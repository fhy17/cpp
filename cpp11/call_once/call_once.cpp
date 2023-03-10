#include <iostream>  // std::cout
#include <thread>    // std::thread, std::this_thread::sleep_for
#include <chrono>    // std::chrono::milliseconds
#include <mutex>     // std::call_once, std::once_flag

int winner;
void set_winner(int x) { winner = x; }
std::once_flag winner_flag;

void wait_100ms(int id) {
    // count to 1000, waiting 1ms between increments:
    for (int i = 0; i < 100; ++i) std::this_thread::sleep_for(std::chrono::microseconds(1));
    // claim to be the winner (only the first such call is executed):
    std::call_once(winner_flag, set_winner, id);
}

int main() {
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i) threads[i] = std::thread(wait_100ms, i + 1);

    std::cout << "waiting for the first among 10 threads to count 100 ms...\n";

    for (auto& th : threads) th.join();
    std::cout << "winner thread: " << winner << '\n';

    return 0;
}