#include "Singleton.hpp"

int main() {
    std::cout << "main begin" << std::endl;
    {
        auto s = Singleton::instance();
        // std::shared_ptr<Singleton> s = std::make_shared<Singleton>();
    }
    // { Singleton2::instance().test(); }
    std::cout << "main end" << std::endl;
}