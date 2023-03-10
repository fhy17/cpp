#pragma once
// 抽象产品类
class AbstractProduct {
public:
    AbstractProduct() {}
    // 抽象产品 接口
    virtual void Play() = 0;
};