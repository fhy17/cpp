#include <gtest/gtest.h>
#include "template.h"

class TemplateTest : public testing::Test {
protected:
    void SetUp() override { tmplate_ptr_ = std::make_shared<Template>("1", "2"); }
    void TearDown() override {}

    TemplatePtr tmplate_ptr_;
};

TEST_F(TemplateTest, testTemplateEaual) {
    std::set<std::string> s{"1", "2"};
    EXPECT_TRUE(tmplate_ptr_->parameterParsSuccess(s));
}

TEST_F(TemplateTest, testTemplateNotEaual) {
    std::set<std::string> s{"1", "3"};
    EXPECT_FALSE(tmplate_ptr_->parameterParsSuccess(s));
}

TEST_F(TemplateTest, testTemplateTooLittle) {
    std::set<std::string> s{"1"};
    EXPECT_FALSE(tmplate_ptr_->parameterParsSuccess(s));
}

TEST_F(TemplateTest, testTemplateTooMuch) {
    std::set<std::string> s{"1", "2", "3"};
    EXPECT_FALSE(tmplate_ptr_->parameterParsSuccess(s));
}