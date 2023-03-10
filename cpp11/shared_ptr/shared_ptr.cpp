#include "shared_ptr.h"

#include <memory>
#include <string>

void sharedPtr() {
    std::shared_ptr<int> pointer(new int(1));

    std::shared_ptr<int> pointer1 = pointer;

    std::shared_ptr<std::string> s(new std::string("AAA"));

    std::shared_ptr<std::string> s1 = std::shared_ptr<std::string>(new std::string("AAA"));

    std::shared_ptr<std::string> p2 = std::make_shared<std::string>();

    std::shared_ptr<std::string> p3 = std::make_shared<std::string>("hello");
}

int main() {
    sharedPtr();
    return 0;
}