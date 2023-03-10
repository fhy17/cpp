#include <gtest/gtest.h>

#include <iostream>
#include <thread>

#include "Singleton1.hpp"
#include "Singleton.hpp"

TEST(singletonCase, testSingleton1) {
    const int THREAD_NUM = 3;
    std::thread t[THREAD_NUM];
    int thread_num = 0;
    while (thread_num < THREAD_NUM) {
        t[thread_num++] = std::thread([]() { auto s = Singleton1::instance(); });
    }
    for (auto &e : t) {
        e.join();
    }

    EXPECT_EQ(count1, 1);
}

TEST(singletonCase, testSingleton) {
    const int THREAD_NUM = 3;
    std::thread t[THREAD_NUM];
    int thread_num = 0;
    while (thread_num < THREAD_NUM) {
        t[thread_num++] = std::thread([]() { auto s = Singleton::instance(); });
    }
    for (auto &e : t) {
        e.join();
    }

    EXPECT_EQ(count, 1);
}
