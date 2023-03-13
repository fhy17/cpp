#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <shared_mutex>
#include <string>

// 函数返回值类型推导
auto func(int i) { return i; }

// 返回值类型推导也可以用在模板中
template <typename T>
auto func(T t) {
    return t;
}

// 函数内如果有多个return语句，它们必须返回相同的类型
auto func(bool flag) {
    if (flag) return 1;
    // else return 2.3;  // error
}

// 如果函数是虚函数，不能使用返回值类型推导
struct A0 {
    // error: virtual function cannot have deduced return type
    // virtual auto func() { return 1; }
};

// 返回类型推导可以用在前向声明中，但是在使用它们之前，必须先定义函数
auto f();                // declared, not yet defined
auto f() { return 42; }  // defined, return type is int

int testF() { return f(); }

// 返回类型推导可以用在递归函数中，但是递归调用必须以至少一个返回语句作为先导，以便编译器推导出返回类型
auto sum(int i) {
    if (i == 1)
        return i;  // return int
    else
        return sum(i - 1) + i;  // ok
}

// lambda表达式参数可以直接是auto
auto lambdaFunc = [](auto a) { return a; };
// cout << lambdaFunc(1) << endl;
// cout << lambdaFunc(2.3f) << endl;

// 变量模板
template <class T>
constexpr T pi = T(3.1415926535897932385L);
// cout << pi<int> << endl;     // 3
// cout << pi<double> << endl;  // 3.14159

// 别名模板
template <typename T, typename U>
struct A {
    T t;
    U u;
};
template <typename T>
using B = A<T, int>;
B<double> b;

// constexpr函数可以使用递归，在C++14中可以使用局部变量和循环
constexpr int factorial(int n) {  // C++11中不可，C++14中可以
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        ret += i;
    }
    return ret;
}

// [[deprecated]]标记
// 修饰类、变、函数等，当程序中使用到了被其修饰的代码时，编译时被产生警告，用户提示开发者该标记修饰的内容将来可能会被丢弃，尽量不要使用
struct [[deprecated]] A1 {};

// 二进制字面量与整形字面量分隔符
int a = 0b0001'0011'1010;
double b = 3.14'1234'1234'1234;

// std::make_unique
struct A2 {};
std::unique_ptr<A2> ptr = std::make_unique<A2>();

// std::shared_timed_mutex与std::shared_lock
// 通过std::shared_timed_mutex和std::shared_lock来实现读写锁，保证多个线程可以同时读，但是写线程必须独立运行，写操作不可以同时和读操作一起进行

struct ThreadSafe {
    mutable std::shared_timed_mutex mutex_;
    int value_;

    ThreadSafe() { value_ = 0; }

    int get() const {
        std::shared_lock<std::shared_timed_mutex> loc(mutex_);
        return value_;
    }

    void increase() {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        value_ += 1;
    }
};

// std::exchange
template <class T, class U = T>
constexpr T exchange(T& obj, U&& new_value) {
    T old_value = std::move(obj);
    obj = std::forward<U>(new_value);
    return old_value;
}

std::vector<int> v;
std::exchange(v, {1, 2, 3, 4});

// std::quoted
// std::quoted用于给字符串添加双引号

std::string str = "hello world";
std::cout << str << std::endl;               // hello world
std::cout << std::quoted(str) << std::endl;  // "hello world"