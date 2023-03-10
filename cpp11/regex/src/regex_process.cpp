#include "regex_process.h"

#include <regex>

// 菜鸟工具 正则表达式 https://c.runoob.com/front-end/854/

namespace RegexArea {
static bool match(const std::string &src, const std::string &match_rules) {
    std::regex pattern(match_rules);
    if (std::regex_match(src, pattern)) {
        return true;
    }
    return false;
}

bool matchIP(const std::string &ip) {
    std::string match_rules = "((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}";
    return match(ip, match_rules);
}

bool matchEmail(const std::string &email) {
    std::string match_rules = "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$";
    return match(email, match_rules);
}

bool matchDomain(const std::string &domain) {
    std::string match_rules = "[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(\\.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+\\.?";
    return match(domain, match_rules);
}

bool matchInternetURL(const std::string &url) {
    std::string match_rules = "^http://([\\w-]+\\.)+[\\w-]+(/[\\w-./?%&=]*)?$";
    std::string match_rules1 = "[a-zA-z]+://[^\\s]*";
    if (match(url, match_rules1) || match(url, match_rules))
        return true;
    else
        return false;
}

bool matchCellphone(const std::string &phone) {
    std::string match_rules = "^(13[0-9]|14[5|7]|15[0|1|2|3|4|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}$";
    return match(phone, match_rules);
}

bool matchTelephone(const std::string &phone) {
    std::string match_rules = "^(\\(\\d{3,4}-)|\\d{3.4}-)?\\d{7,8}$";
    return match(phone, match_rules);
}

bool matchTelephoneAll(const std::string &phone) {
    std::string match_rules =
        "((\\d{11})|^((\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})|(\\d{4}|\\d{3})-(\\d{7,8})-(\\d{4}|\\d{3}|\\d{2}|\\d{1})|("
        "\\d{7,8})-(\\d{4}|\\d{3}|\\d{2}|\\d{1}))$)";
    return match(phone, match_rules);
}

bool matchID(const std::string &id) {
    std::string match_rules = "(^\\d{15}$)|(^\\d{18}$)|(^\\d{17}(\\d|X|x)$)";
    return match(id, match_rules);
}

}  // namespace RegexArea