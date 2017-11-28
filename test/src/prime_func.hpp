#ifndef PRIME_FUNC_HPP
#define PRIME_FUNC_HPP

#include <limits>
#include <cmath>

#define MAX std::numeric_limits<int>::max()

int prime(int n)
{
    int i,j,count=0;

    if (n == 1) {
        return 2;
    }
    for(i=3;i<=MAX;i+=2)
    {
        int isPrime=1;
        int jMax = sqrt(i);
        for(j=3;j<=jMax;j+=2)
        {
            if(i%j==0)
            {
                isPrime=0;
                break;
            }
        }
        if(isPrime)
        {
            if(++count==n)
            {
                return i;
            }
        }
    }
}

#endif