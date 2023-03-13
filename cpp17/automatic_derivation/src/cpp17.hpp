#pragma once
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <filesystem>

// 主要新特性如下：

// 构造函数模板推导
// 结构化绑定
// if - switch语句初始化
// 内联变量
// 折叠表达式
// constexpr
// lambda表达式
// namespace嵌套
// __has_include预处理表达式
// 在lambda表达式用* this捕获对象副本
// 新增Attribute
// 字符串转换
// std::variant
// std::optional
// std::any
// std::apply
// std::make_from_tuple
// as_const
// std::string_view
// file_system
// std::shared_mutex

// 构造函数模板推导
std::pair p(1, 2.2);        // c++17 自动推导
std::vector v = {1, 2, 3};  // c++17

// if-switch语句初始化
int GetValue();
if ((int a = GetValue()); a < 101) {
    cout << a;
}

// 内联变量
// header file
struct A {
    static const int value;
};
inline int const A::value = 10;

// ==========或者========
struct A {
    inline static const int value = 10;
};

// 折叠表达式
template <typename... Ts>
auto sum(Ts... ts) {
    return (ts + ...);
}
int a{sum(1, 2, 3, 4, 5)};  // 15
std::string a{"hello "};
std::string b{"world"};
std::cout << sum(a, b) << std::endl;  // hello world

// constexpr lambda表达式，可以用于在编译期进行计算
// 注意：constexpr函数有如下限制：

// 函数体不能包含汇编语句、goto语句、label、try块、静态变量、线程局部存储、没有初始化的普通变量，不能动态分配内存，不能有new
// delete等，不能虚函数
constexpr auto lamb = [](int n) { return n * n; };
static_assert(lamb(3) == 9, "a");

// namespace嵌套
namespace A {
namespace B {
namespace C {
void func();
}
}  // namespace B
}  // namespace A

// c++17，更方便更舒适
namespace A::B::C {
void func();
}  // namespace A::B::C

// file_system
namespace fs = std::filesystem;
fs::create_directory(dir_path);
fs::copy_file(src, dst, fs::copy_options::skip_existing);
fs::exists(filename);
fs::current_path(err_code);