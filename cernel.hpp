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
                    mCV.wait(lock);
                    if(mStatus != Running) //If threadpool status does not imply running
                        break; //Break out of loop, ending thread in the process
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
            for(std::thread& worker : mWorkers)
            {
                worker.join();
            }
        }
        template<typename RT>
        inline std::future<RT> queueTask(std::function<RT()> _task, bool _execute = false)
        {
            std::promise<RT> promise;
            std::function<void()> func([&_task, &promise]() -> RT {
                RT val = _task();
                promise.set_value(val);
            });

            mTasksMutex.lock();
            mTasks.emplace(func);
            mTasksMutex.unlock();
            if(_execute) flush();
            return promise.get_future();
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