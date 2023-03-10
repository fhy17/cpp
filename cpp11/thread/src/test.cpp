
#include "function.hpp"

#include <iostream>

int main() {
    {
        auto t = Test::instance();
        // t->begin();
        t->start();

        std::this_thread::sleep_for(std::chrono::seconds(3));
        t->submitTask();

        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "end" << std::endl;
        // t->end();
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "main  end" << std::endl;
}