#pragma once

#include <string>
#include <set>
#include <memory>
#include <iostream>

class Template {
public:
    template <typename... Args>
    Template(Args &&...args) {
        init(std::forward<Args>(args)...);
    }

    ~Template() { set_.clear(); }

    void show() const {
        for (auto &e : set_) std::cout << e << " ";
        std::cout << std::endl;
    }

    bool parameterParsSuccess(const std::set<std::string> &in) {
        if (in.size() != set_.size()) return false;
        auto it_in = in.begin();
        auto it_set = set_.begin();

        for (; it_in != in.end() && it_set != set_.end(); ++it_in, ++it_set) {
            if (*it_in != *it_set) return false;
        }
        return true;
    }

private:
    // 用于终止迭代的基函数
    template <typename T>
    void init(T &&arg) {
        insert(std::forward<T>(arg));
    }

    // 可变参数函数模板
    template <typename T, typename... Ts>
    void init(T &&arg, Ts &&...args) {
        insert(std::forward<T>(arg));
        init(std::forward<Ts>(args)...);  // 先使用forward函数处理后，再解包，然后递归
    }

    void insert(std::string &&rule) { set_.emplace(rule); }

private:
    std::set<std::string> set_;
};

typedef std::shared_ptr<Template> TemplatePtr;