#include <time.h>
#include <iostream>

unsigned factorial(unsigned n)
{
    if (n == 1 || n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

int main()
{
    clock_t start = clock();
    for (unsigned i = 0; i < 10000000; i++)
    {
        factorial(10);
    }
    clock_t end = clock();
    double seconds = 
    std::cout << seconds << " s" << std::endl;
}
