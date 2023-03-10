#pragma once

#include <iostream>

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
struct A {
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