#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <format>
#include <functional>
#include <time.h>

double factorial(double n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void Func(std::string name, double n, unsigned iterations, std::string &output)
{
    double result;
    for (unsigned i = 0; i < iterations; i++)
    {
        result = factorial(n);
    }
    output = std::format("{}: {}\n", name, result);
}

void consistent_run(double n, unsigned iterations)
{
    std::string output;
    Func("t1", n, iterations, std::ref(output));
    std::cout << output;
    Func("t2", n, iterations, std::ref(output));
    std::cout << output;
}

void thread_run(double n, unsigned iterations)
{
    std::string output1;
    std::string output2;
    std::thread thread1(Func, "f1", n, iterations, std::ref(output1));
    std::thread thread2(Func, "f2", n, iterations, std::ref(output2));
    thread1.join();
    thread2.join();
    std::cout << output1 << output2;
}

void stopwatch(std::function<void(double, unsigned)> task, double n, unsigned iterations)
{
    clock_t start = clock();
    task(n, iterations);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << std::format("{} s\n", seconds);
}

int main()
{
    double n = 25;
    unsigned int iterations = 10'000'000;
    std::cout << std::format("n: {}\niterations: {}\n", n, iterations);
    stopwatch(thread_run, n, iterations);
    stopwatch(consistent_run, n, iterations);

    return 0;
}
