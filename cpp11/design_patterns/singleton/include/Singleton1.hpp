#pragma once

// 单例模式1
#include <iostream>
#include <mutex>

std::atomic<int> count1 = 0;

class Singleton1 {
public:
    static Singleton1* instance() {
        if (instance_ == nullptr) {
            mtx_.lock();
            if (instance_ == nullptr) {
                instance_ = new Singleton1();
                // std::cout << "new Singleton" << std::endl;
            }
            mtx_.unlock();
        }
        return instance_;
    }

private:
    Singleton1() {
        // std::cout << "Singleton1 constructor" << std::endl;
        ++count1;
    }
    Singleton1(const Singleton1& rsh) = delete;
    Singleton1& operator=(const Singleton1& rsh) = delete;

    ~Singleton1() {
        //  std::cout << "Singleton1 destructor" << std::endl;
    }

    static Singleton1* instance_;
    static std::mutex mtx_;

    class GC {
    public:
        ~GC() {
            if (instance_ != nullptr) {
                delete instance_;
                instance_ = nullptr;
            }
        }
    };
    static GC gc;
};

Singleton1* Singleton1::instance_ = nullptr;
std::mutex Singleton1::mtx_;