#include <vector>
#include <iostream>
using namespace std;

// 委托构造函数允许在同一个类中一个构造函数调用另外一个构造函数，可以在变量初始化时简化操作
class A {
public:
    A() {}
    A(int a) { a_ = a; }

    A(int a, int b) : A(a) { b_ = b; }

    A(int a, int b, int c) : A(a, b) { c_ = c; }

private:
    int a_;
    int b_;
    int c_;
};

int main() {
    A a;
    A a1(1);
    A a2(1, 2);
    A a3(1, 2, 3);
    return 0;
}