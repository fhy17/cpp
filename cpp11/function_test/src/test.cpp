#include "function2.hpp"
#include "function.hpp"
#include "function_cb.hpp"

#include <iostream>

int main() {
    if (5 == test1()) std::cout << "pass" << std::endl;

    std::shared_ptr<Proxy> cmd = std::make_shared<Proxy>();
    int y = 7;

    // cmd->place_order(1, y);

    // TestProxy::instance()->activate("", 1, 1);
    func_cb();
}