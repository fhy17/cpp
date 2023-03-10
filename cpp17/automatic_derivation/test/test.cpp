#include <gtest/gtest.h>

#include "auto_return.hpp"

TEST(autoReturnTestCase, testChar) {
    char one = 1;
    char one_negative = -1;
    char zero = 0;
    EXPECT_EQ(func(one), one);
    EXPECT_EQ(func(zero), zero);
    EXPECT_EQ(func(one_negative), one_negative);

    EXPECT_EQ(func(CHAR_MAX), CHAR_MAX);
    EXPECT_EQ(func(CHAR_MIN), CHAR_MIN);
}