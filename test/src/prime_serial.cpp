#include "prime_func.hpp"

#include <iostream>

int main(int argc, char** argv)
{

    prime(1000000);
    prime(1000000);
    prime(1000000);
    prime(1000000);
    prime(1000000);
    prime(1000000);
    prime(1000000);
    int pr = prime(1000000);

    std::cout << "1000000th prime is: " << pr << std::endl;

    return 0;
}