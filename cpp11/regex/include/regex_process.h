#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <regex>
#include <set>
#include <initializer_list>

namespace RegexArea {

bool matchIP(const std::string &ip);

bool matchEmail(const std::string &email);

bool matchDomain(const std::string &domain);

bool matchInternetURL(const std::string &url);

bool matchCellphone(const std::string &phone);

bool matchTelephone(const std::string &phone);

bool matchTelephoneAll(const std::string &phone);

bool matchID(const std::string &id);

class RegexBase {
public:
    RegexBase(std::initializer_list<std::string> &l) {
        for (auto &e : l) {
            try {
                auto tmp = new std::regex(e);
                if (tmp) pattern_.emplace(tmp);
            } catch (std::exception &ex) {
                std::cout << "error:" << ex.what() << std::endl;
            }
        }
        std::cout << "RegexBase" << std::endl;
    }

    virtual ~RegexBase() {
        for (auto &e : pattern_) delete e;
        pattern_.clear();
        // if (pattern_) delete pattern_;
        std::cout << "~RegexBase" << std::endl;
    }

    bool match(const std::string &src) {
        bool res = true;
        for (auto &e : pattern_) {
            res = res & std::regex_match(src, *e);
        }
        return res;
    }

private:
    std::set<std::regex *> pattern_;
};
typedef std::shared_ptr<RegexBase> RegexBasePtr;

class Regex {
public:
    template <typename... Args>
    Regex(Args &&...args) {
        init(std::forward<Args>(args)...);
    }

    virtual ~Regex() {
        for (auto &e : regex_) delete e;
        regex_.clear();
    }

    bool match(const std::string &src) {
        bool res = true;
        for (auto &e : regex_) {
            res = res & std::regex_match(src, *e);
        }
        return res;
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

    void insert(std::string rule) {
        try {
            auto tmp = new std::regex(rule);
            regex_.emplace(tmp);
        } catch (std::exception &e) {
            // std::cout << rule << ", " << e.what() << std::endl;
        }
    }

private:
    std::set<std::regex *> regex_;
};

typedef std::shared_ptr<Regex> RegexPtr;

class RegexIP : public Regex {
public:
    RegexIP(
        const std::string &rule = "((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}")
        : Regex(rule) {}

    ~RegexIP() override {}
};

class RegexEmail : public Regex {
public:
    RegexEmail(const std::string &rule = "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$") : Regex(rule) {}

    ~RegexEmail() override {}
};

class RegexDomain : public Regex {
public:
    RegexDomain(const std::string &rule = "[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(\\.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+\\.?")
        : Regex(rule) {}

    ~RegexDomain() override {}
};

class RegexURL : public Regex {
public:
    RegexURL(const std::string &rule = "^(http|https)://([\\w-]+\\.)+[\\w-]+(/[\\w-./?%&=]*)?$",
             const std::string &rule1 = "[a-zA-Z]+://[^\\s]*")
        : Regex(rule, rule1) {}

    ~RegexURL() override {}
};

class RegexCellphone : public Regex {
public:
    RegexCellphone(const std::string &rule = "^(13[0-9]|14[5|7]|15[0|1|2|3|4|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$")
        : Regex(rule) {}

    ~RegexCellphone() override {}
};

class RegexTelephone : public Regex {
public:
    RegexTelephone(const std::string &rule =
                       "((\\d{11})|^((\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})-(\\d{4}|\\d{3}"
                       "|\\d{2}|\\d{1})|(\\d{7,8})-(\\d{4}|\\d{3}|\\d{2}|\\d{1}))$)")
        : Regex(rule) {}

    ~RegexTelephone() override {}
};

class RegexID : public Regex {
public:
    RegexID(const std::string &rule = "(^\\d{15}$)|(^\\d{18}$)|(^\\d{17}(\\d|X|x)$)") : Regex(rule) {}

    ~RegexID() override {}
};

}  // namespace RegexArea