#include <iostream>
#include <future>
#include <thread>

int main() {
    auto begin = std::chrono::system_clock::now();

    auto asyncLazy = std::async(std::launch::deferred, []() {
        std::cout << "asyncLazy thread id: " << std::this_thread::get_id() << std::endl;
        return std::chrono::system_clock::now();
    });

    auto asyncEager = std::async(std::launch::async, []() {
        std::cout << "asyncEager thread id: " << std::this_thread::get_id() << std::endl;
        return std::chrono::system_clock::now();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    auto lazyStart = asyncLazy.get() - begin;
    auto eagerStart = asyncEager.get() - begin;

    auto lazyDuration = std::chrono::duration<double>(lazyStart).count();
    auto eagerDuration = std::chrono::duration<double>(eagerStart).count();

    std::cout << "asyncLazy evaluated after : " << lazyDuration << " seconds." << std::endl;
    std::cout << "asyncEager evaluated after: " << eagerDuration << " seconds." << std::endl;

    std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;

    return 0;
}
