#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <chrono>
#include <format>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string get_time_now()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 10000;

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%H:%M:%S")
        << ":" << std::setw(5) << std::setfill('0') << millis.count();

    return oss.str();
};

void coin_sharing(int &coins, std::mutex &coins_mutex, std::string name, int &thief_coins, int &companion_coins)
{
    while (true)
    {
        std::lock_guard<std::mutex> lock(coins_mutex);
        if (thief_coins < companion_coins || (thief_coins == companion_coins && coins > 1))
        {
            coins -= 1;
            thief_coins += 1;
            std::cout << std::format("{} | {} | thief coins: {}, companion coins: {}, coins: {}\n", get_time_now(), name, thief_coins, companion_coins, coins);
        }
        if (coins == 0 || (coins == 1 && thief_coins == companion_coins))
        {
            break;
        }
    }
}

void share_coins(int coins)
{
    std::mutex coins_mutex;
    std::cout << std::format("---- Run with {} coins ----\n\n", coins);
    int Bob_coins = 0;
    int Tom_coins = 0;

    std::thread Bob_thread(coin_sharing, std::ref(coins), std::ref(coins_mutex), "Bob", std::ref(Bob_coins), std::ref(Tom_coins));
    std::thread Tom_thread(coin_sharing, std::ref(coins), std::ref(coins_mutex), "Tom", std::ref(Tom_coins), std::ref(Bob_coins));

    Bob_thread.join();
    Tom_thread.join();

    std::cout << std::format("\ncoins: {}\nBob coins: {}\nTom coins: {}\n\n", coins, Bob_coins, Tom_coins);
}

int main()
{
    int input_coins[6]{0, 1, 2, 5, 100, 101};

    for (int i = 0; i < 6; i++)
    {
        share_coins(input_coins[i]);
    }
}