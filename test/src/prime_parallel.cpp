#include <cernel.hpp>

#include "prime_func.hpp"

int main(int argc, char** argv)
{
    ccy::cernel pool;


    std::future<int> task = pool.queueTask<int>([]() -> int {
        return prime(1000000);
    });
    std::future<int> task1 = pool.queueTask<int>([]() -> int {http://ilias.uni-stuttgart.de/
        return prime(1000000);
    });
    std::future<int> task2 = pool.queueTask<int>([]() -> int {
        return prime(1000000);
    });
    std::future<int> task3 = pool.queueTask<int>([]() -> int {
        return prime(1000000);
    });
    std::future<int> task4 = pool.queueTask<int>([]() -> int {
        return prime(1000000);
    });
    std::future<int> task5 = pool.queueTask<int>([]() -> int {
        return prime(1000000);
    });
    std::future<int> task6 = pool.queueTask<int>([]() -> int {
        return prime(1000000);
    });
    std::future<int> task7 = pool.queueTask<int>([]() -> int {
        return prime(1000000);
    });

    pool.flush();

    task.wait();
    task1.wait();
    task2.wait();
    task3.wait();
    task4.wait();
    task5.wait();
    task6.wait();
    task7.wait();

    std::cout << "1000000th prime is: " << task.get() << std::endl;
    return 0;
}
