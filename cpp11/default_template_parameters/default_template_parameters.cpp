#include <iostream>

using namespace std;

// 对于函数模板，参数的填充顺序是从左到右的
template <typename R, typename U = int>
R func1(U val) {
    return val;
}

template <typename R = int, typename U>
R func2(U val) {
    return val;
}

// 同时C++11支持变长参数模板
template <typename T>
void func(const T& t){
    cout << t << '\n';
}

template <typename T, typename ... Args>
void func(const T& t, Args ... args){
    cout << t << ',';
    func(args...);
}

int main() {
    cout << func1<int, double>(99.9) << endl;     // 99
    cout << func1<double, double>(99.9) << endl;  // 99.9
    cout << func1<double>(99.9) << endl;          // 99.9
    cout << func1<int>(99.9) << endl;             // 99
    cout << func2<int, double>(99.9) << endl;     // 99
    cout << func1<double, double>(99.9) << endl;  // 99.9
    cout << func2<double>(99.9) << endl;          // 99.9
    cout << func2<int>(99.9) << endl;             // 99
    return 0;
}