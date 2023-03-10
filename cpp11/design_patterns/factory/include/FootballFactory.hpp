#pragma once

// 具体产品工厂类
#include "AbstractFactory.hpp"
#include "Football.hpp"
#include "FootballShirt.hpp"

class FootballFactory : public AbstractFactory {
public:
    AbstractProduct* GetProduct() { return new Football(); }
    AbstractShirt* GetShirt() { return new FootballShirt(); }
};