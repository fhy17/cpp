#include "automatic_derivation.hpp"

#include <iostream>
#include <vector>

int main() {
    // f();
    std::vector v = {1, 2, 3};  // c++17
    for (auto &e : v) std::cout << e << ", ";
    std::cout << std::endl;
}