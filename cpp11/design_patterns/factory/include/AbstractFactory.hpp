#pragma once
// 抽象工厂类
#include "AbstractProduct.hpp"
#include "AbstractShirt.hpp"

class AbstractFactory {
public:
    virtual AbstractProduct* GetProduct() = 0;

    virtual AbstractShirt* GetShirt() = 0;
};