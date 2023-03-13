#include <iostream>
#include <vector>

int main() {
    // 让编译器在编译器就推导出变量的类型，可以通过=右边的类型推导出变量的类型
    auto a = 10;  // 10是int型，可以自动推导出a是int
    std::cout << a << std::endl;

    // 相对于auto用于推导变量类型，而decltype则用于推导表达式类型，这里只用于编译器分析表达式的类型，表达式实际不会进行运算
    const int &i = 1;
    int x = 2;
    decltype(i) b = 2;  // b是const int&
}