#pragma once

// 具体产品工厂类
#include "AbstractFactory.hpp"
#include "Volleyball.hpp"
#include "VolleyballShirt.hpp"

class VolleyballFactory : public AbstractFactory {
public:
    AbstractProduct* GetProduct() { return new Volleyball(); }
    AbstractShirt* GetShirt() { return new VolleyballShirt(); }
};