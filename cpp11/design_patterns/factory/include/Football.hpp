#pragma once
// 具体产品类
#include <iostream>

#include "AbstractProduct.hpp"

class Football : public AbstractProduct {
public:
    Football() { Play(); }
    void Play() { std::cout << "play Football" << std::endl; }
};