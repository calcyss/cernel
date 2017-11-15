#include <iostream>

#include <cernel.hpp>
#include <cmath>

int main()
{
    ccy::cernel pool;

    std::future<float> value = pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    }, true);

    std::cout << "Square root of 65: " << value.get() << std::endl;

    return 0;
}