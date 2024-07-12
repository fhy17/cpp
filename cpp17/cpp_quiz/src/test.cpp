#include <iostream>
#include <memory>
#include <functional>

#include <mutex>

std::mutex score_exchange_mutex;
using namespace std;

void f1(std::function<void(int)> fo) {
    auto lock = std::make_shared<std::unique_lock<std::mutex>>(score_exchange_mutex);
    auto f = [fo, lock]() {
        fo(0);
        std::cout << "f" << std::endl;
    };
    f();
}
int main() {
    auto f = [](int err) { std::cout << err << std::endl; };
    f1(f);
    return 0;
}