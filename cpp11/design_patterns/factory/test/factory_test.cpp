// 工厂模式 使用示例

#include <gtest/gtest.h>

#include "AbstractFactory.hpp"
#include "AbstractProduct.hpp"
#include "FootballFactory.hpp"
#include "VolleyballFactory.hpp"
#include "FootballShirt.hpp"
#include "VolleyballShirt.hpp"

void AbstractFactoryTest() {
    AbstractProduct *pro = nullptr;
    AbstractFactory *fac = nullptr;
    AbstractShirt *foo_shirt = nullptr;
    AbstractShirt *vol_shirt = nullptr;

    fac = new FootballFactory();
    pro = fac->GetProduct();
    foo_shirt = fac->GetShirt();

    fac = new VolleyballFactory();
    pro = fac->GetProduct();
    vol_shirt = fac->GetShirt();
}

TEST(FactoryCase, testFactory) {
    AbstractFactoryTest();
    EXPECT_TRUE(true);
}
