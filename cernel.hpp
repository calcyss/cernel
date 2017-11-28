#ifndef CCY_CERNEL_HPP
#define CCY_CERNEL_HPP

//Headers for parallelism
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>

//Container headers
#include <vector>
#include <queue>

//Misc headers
#include <functional>
#include <utility>
#include <string>
#include <iostream>

std::mutex m;

void log(std::string msg)
{
    m.lock();
    std::cout << msg << std::endl;
    m.unlock();
}

namespace ccy
{
    class cernel
    {
    public:
        //Enum/Class definitions
        enum Status {
            Stopped = 0,
            Running,
        };

        //Constructor/Destructor
        cernel(unsigned int _nWorkers = std::thread::hardware_concurrency())
        {
            mStatus = Running;
            std::function<void()> worker;

            worker = [this](){
                while(true)
                {
                    std::unique_lock<std::mutex> lock(mStatusMutex); //CV for status updates
                    if(mStatus != Running) //Same thing as below, in case a thread "arrives later".
                    {
                        break;
                    } //Break out of loop, ending thread in the process
                    mCV.wait(lock);
                    if(mStatus != Running) //If threadpool status does not imply running
                    {
                        break;
                    } //Break out of loop, ending thread in the process
                    else //If threadpool is in running state
                    {
                        lock.unlock(); //Unlock state
                        while(true) //Loop until no tasks are left
                        {
                            mTasksMutex.lock(); //Lock task queue
                            if(mTasks.empty()) //IF no tasks left, break out of loop and return to waiting
                            {
                                mTasksMutex.unlock();
                                break;
                            }
                            else //Else, retrieve a task, unlock the task queue and execute the task
                            {
                                std::function<void()> task = mTasks.front();
                                mTasks.pop();
                                mTasksMutex.unlock();
                                task(); //Execute task
                            }
                        }
                    }
                }
            };

            for(int i = 0; i < _nWorkers; i++)
            {
                std::thread tWorker(worker);
                mWorkers.push_back(std::move(tWorker));
            }
        }
        ~cernel()
        {
            if(mStatus == Running) stop();
        }
        inline void stop()
        {
            mStatusMutex.lock();
            mStatus = Stopped;
            mStatusMutex.unlock();
            mCV.notify_all();

            for(std::thread& t : mWorkers)
            {
                t.join();
            }
        }
        template<typename RT>
        inline std::future<RT> queueTask(std::function<RT()> _task, bool _execute = false)
        {
            if(mStatus == Running)
            {
                auto promise = std::make_shared<std::promise<RT>>();
                std::function<void()> func([promise, task = std::move(_task)]() -> RT {
                    RT val = task();
                    promise->set_value(val);
                });

                mTasksMutex.lock();
                mTasks.emplace(func);
                mTasksMutex.unlock();
                if(_execute)
                {
                    flush();
                }
                return promise->get_future();
            }
        }
        inline std::future<void> queueTask(std::function<void()> _task, bool _execute = false)
        {
            if(mStatus == Running)
            {
                auto promise = std::make_shared<std::promise<void>>();
                std::function<void()> func([promise, task = std::move(_task)]() -> void {
                    task();
                    promise->set_value();
                });

                mTasksMutex.lock();
                mTasks.emplace(func);
                mTasksMutex.unlock();
                if(_execute)
                {
                    flush();
                }
                return promise->get_future();
            }
        }
        inline void flush()
        {
            mCV.notify_all();
        }
    private:
        //Misc
        int mStatus;

        //Containers
        std::vector<std::thread> mWorkers;
        std::queue<std::function<void()>> mTasks;

        //Mutexes
        std::mutex mTasksMutex;
        std::mutex mStatusMutex;

        //Condition variable
        std::condition_variable mCV;
    };
}

#endif
