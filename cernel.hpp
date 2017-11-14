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
            mStatus = Stopped;
            std::function<void()> worker;

            for(int i = 0; i < _nWorkers; i++)
            {
                std::thread tWorker(worker);
                mWorkers.push_back(std::move(tWorker));
            }
        }
        ~cernel()
        {

        }

        //Public member functions
        void start()
        {

        }
        void stop()
        {

        }
        template<typename RT(typename AT...)>
        std::future<RT> queueTask(std::function<RT(AT)> _task)
        {
            std::function<void()> realTask = [](){

            };
        }
    private:
        //Misc
        int mStatus;

        //Containers
        std::vector<std::thread> mWorkers;
        std::priority_queue<std::function<void()>> mTasks;

        //Mutexes
        std::mutex mTasksMutex;
    };
}

#endif