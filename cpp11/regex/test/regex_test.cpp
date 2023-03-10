#include <gtest/gtest.h>

#include "regex_process.h"

TEST(regexTestCase, testIP) {
    RegexArea::RegexPtr regex = std::make_shared<RegexArea::RegexIP>();
    EXPECT_FALSE(regex->match(std::string("0.0.0")));
    EXPECT_FALSE(regex->match(std::string("0.0.0.0.0")));
    EXPECT_FALSE(regex->match(std::string("0.0.0.256")));
    EXPECT_FALSE(regex->match(std::string("-1.0.0.0")));
    EXPECT_FALSE(regex->match(std::string("0..0.0")));
    EXPECT_TRUE(regex->match(std::string("0.0.0.0")));
    EXPECT_TRUE(regex->match(std::string("127.0.0.0")));
    EXPECT_TRUE(regex->match(std::string("255.255.255.255")));
}

TEST(regexTestCase, testUrl) {
    RegexArea::RegexPtr regex = std::make_shared<RegexArea::RegexURL>();
    EXPECT_TRUE(regex->match(std::string("https://c.runoob.com")));
    EXPECT_TRUE(regex->match(std::string("http://c.runoob.com")));
    EXPECT_TRUE(regex->match(std::string("https://www.baidu.com/")));
    EXPECT_TRUE(regex->match(std::string("https://www.baidu.com/")));
    // EXPECT_TRUE(regex->match(std::string("www.baidu.com/")));
    // EXPECT_TRUE(regex->match(std::string("www.baidu.com")));
}

TEST(regexTestCase, testID) {
    RegexArea::RegexPtr regex = std::make_shared<RegexArea::RegexID>();
    EXPECT_TRUE(regex->match(std::string("510623199711115118")));
    EXPECT_TRUE(regex->match(std::string("51062319971111511X")));
    EXPECT_TRUE(regex->match(std::string("51062319971111511x")));
    EXPECT_FALSE(regex->match(std::string("51062319971111511")));
    EXPECT_FALSE(regex->match(std::string("5106231997111151X")));
    EXPECT_FALSE(regex->match(std::string("5106231997111151x")));
    EXPECT_FALSE(regex->match(std::string("5106231997111151188")));
    EXPECT_FALSE(regex->match(std::string("510623199711115118X")));
    EXPECT_FALSE(regex->match(std::string("510623199711115118x")));
}