#include <iostream>

#include <cernel.hpp>
#include <cmath>

int main()
{
    ccy::cernel pool;

    std::future<float> value = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });
    std::future<float> value1 = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });
    std::future<float> value2 = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });
    std::future<float> value3 = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });
    std::future<float> value4 = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });
    std::future<float> value5 = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });
    std::future<float> value6 = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });
    std::future<float> value7 = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    });

    pool.flush();

    value1.wait();
    value2.wait();
    value3.wait();
    value4.wait();
    value5.wait();
    value6.wait();
    value7.wait();

    std::cout << "Square root of 65: " << value.get() << std::endl;

    return 0;
}