#pragma once

#include "AbstractShirt.hpp"
#include <iostream>

class VolleyballShirt : public AbstractShirt {
public:
    VolleyballShirt() { wearShirt(); }
    void wearShirt() { std::cout << "wear vollyeball shirt" << std::endl; }
};