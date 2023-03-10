#include <iostream>

void swap(int &x, int &y) {
    x = x ^ y;  // 只能对int,char..
    y = x ^ y;
    x = x ^ y;

    // x ^= y ^= x;
}

int main() {
    int x = 1;
    int y = 3;
    std::cout << x << ", " << y << std::endl;
    swap(x, y);
    std::cout << x << ", " << y << std::endl;
    return 0;
}