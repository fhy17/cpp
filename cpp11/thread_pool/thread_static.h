#ifndef THREAD_STATIC_H
#define THREAD_STATIC_H

#include <iostream>
#include <thread>
// #include <unistd.h>

void func(int id) {
    static int x = 0;
    int count = 10;
    while (--count) {
        // usleep(1000);
        ++x;
        std::cout << id << " " << x << std::endl;
    }
}

void threadTest() {
    std::thread t1(func, 1);
    std::thread t2(func, 2);

    t1.join();
    t2.join();
}

#endif  // THREAD_STATIC_H