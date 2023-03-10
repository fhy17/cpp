#pragma once

// 具体产品类
#include <iostream>

#include "AbstractProduct.hpp"

class Volleyball : public AbstractProduct {
public:
    Volleyball() { Play(); }
    void Play() { std::cout << "play Volleyball" << std::endl; }
};