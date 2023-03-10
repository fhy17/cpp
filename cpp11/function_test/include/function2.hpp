#pragma once

#include <iostream>
#include <functional>

using cbType = std::function<void()>;
class A {
public:
    void bindCB(cbType cb) { cb_ = cb; }
    void fun() {
        if (cb_) cb_();
    }

private:
    cbType cb_;
};

class B {
public:
    int fun() {
        int id = 1;
        int x = 3;
        auto fo = [&id, &x]() {
            ++id;
            id += x;
        };

        A a;
        a.bindCB([&fo, &id]() { fo(); });
        a.fun();
        return id;
    }
};

int test1() {
    B b;
    return b.fun();
}