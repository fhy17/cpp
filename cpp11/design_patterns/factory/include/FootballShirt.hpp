#pragma once

#include "AbstractShirt.hpp"
#include <iostream>

class FootballShirt : public AbstractShirt {
public:
    FootballShirt() { wearShirt(); }
    void wearShirt() { std::cout << "wear Football Shirt" << std::endl; }
};