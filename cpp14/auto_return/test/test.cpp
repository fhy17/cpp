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

TEST(autoReturnTestCase, testShort) {
    short one = 1;
    short one_negative = -1;
    short zero = 0;
    EXPECT_EQ(func(one), one);
    EXPECT_EQ(func(zero), zero);
    EXPECT_EQ(func(one_negative), one_negative);

    EXPECT_EQ(func(SHRT_MAX), SHRT_MAX);
    EXPECT_EQ(func(SHRT_MIN), SHRT_MIN);
}

TEST(autoReturnTestCase, testInt) {
    int one = 1;
    int one_negative = -1;
    int zero = 0;
    EXPECT_EQ(func(one), one);
    EXPECT_EQ(func(zero), zero);
    EXPECT_EQ(func(one_negative), one_negative);

    EXPECT_EQ(func(INTMAX_MAX), INTMAX_MAX);
    EXPECT_EQ(func(INTMAX_MIN), INTMAX_MIN);
}

TEST(autoReturnTestCase, testLong) {
    long one = 1;
    long one_negative = -1;
    long zero = 0;
    EXPECT_EQ(func(one), one);
    EXPECT_EQ(func(zero), zero);
    EXPECT_EQ(func(one_negative), one_negative);

    EXPECT_EQ(func(INTMAX_MAX), INTMAX_MAX);
    EXPECT_EQ(func(INTMAX_MIN), INTMAX_MIN);
}

TEST(autoReturnTestCase, testLongLong) {
    long long one = 1;
    long long one_negative = -1;
    long long zero = 0;
    EXPECT_EQ(func(one), one);
    EXPECT_EQ(func(zero), zero);
    EXPECT_EQ(func(one_negative), one_negative);

    EXPECT_EQ(func(INTMAX_MAX), INTMAX_MAX);
    EXPECT_EQ(func(INTMAX_MIN), INTMAX_MIN);
}

TEST(autoReturnTestCase, testFloat) {
    float one = 1.0;
    float one_negative = -1.0;
    float zero = 0.0;
    EXPECT_EQ(func(one), one);
    EXPECT_EQ(func(zero), zero);
    EXPECT_EQ(func(one_negative), one_negative);

    EXPECT_EQ(func(FLT_MAX), FLT_MAX);
    EXPECT_EQ(func(FLT_MIN), FLT_MIN);
}

TEST(autoReturnTestCase, testDouble) {
    double one = 1.0;
    double one_negative = -1.0;
    double zero = 0.0;
    EXPECT_EQ(func(one), one);
    EXPECT_EQ(func(zero), zero);
    EXPECT_EQ(func(one_negative), one_negative);

    EXPECT_EQ(func(DBL_MAX), DBL_MAX);
    EXPECT_EQ(func(DBL_MIN), DBL_MIN);
}
