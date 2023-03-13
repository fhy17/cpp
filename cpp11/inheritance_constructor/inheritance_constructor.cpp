#include <vector>
#include <iostream>
using namespace std;

// 继承构造函数可以让派生类直接使用基类的构造函数，如果有一个派生类，我们希望派生类采用和基类一样的构造方式，可以直接使用基类的构造函数，而不是再重新写一遍构造函数
struct Base {
    Base() {}
    Base(int a) { a_ = a; }

    Base(int a, int b) : Base(a) { b_ = b; }

    Base(int a, int b, int c) : Base(a, b) { c_ = c; }

    int a_;
    int b_;
    int c_;
};

struct Derived : Base {
    using Base::Base;  // 只需要使用using Base::Base继承构造函数
};

int main() {
    Derived a(1, 2, 3);
    return 0;
}