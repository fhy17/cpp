#pragma once
// 单例模式 推存使用
#include <iostream>
#include <atomic>
#include <mutex>
#include <memory>

std::atomic<int> count = 0;

class Singleton {
public:
    static Singleton* instance() {
        static Singleton self;
        return &self;
    }

private:
    Singleton() {
        std::cout << "Singleton constructor" << std::endl;
        ++count;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator==(const Singleton&) = delete;

    ~Singleton() { std::cout << "Singleton destructor" << std::endl; }
};

class Singleton2 {
private:
    Singleton2() {}
    static Singleton2* instance;
    static std::once_flag flag;
    static void init() { instance = new Singleton2(); }

public:
    static Singleton2* getInstance() {
        std::call_once(flag, init);
        return instance;
    }
};

Singleton2* Singleton2::instance = nullptr;
std::once_flag Singleton2::flag;