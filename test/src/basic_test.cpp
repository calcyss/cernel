#include <iostream>

#include <cernel.hpp>
#include <cmath>

int main()
{
    ccy::cernel pool;

    float value;

    pool.queueTask<float>([]() -> float {
        return (float)sqrt(65);
    }, true);

    std::cout << "Square root of 65: " << value << std::endl;

    return 0;
}