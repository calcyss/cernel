#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "prime_func.hpp"

using namespace std::chrono_literals;


int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2s);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";


    double last_time = 0.0;
    while(true)
    {
        prime(100000);
        auto now =
    }


    return 0;
}