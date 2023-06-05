#include "map_test.h"
#include <map>
#include <string>
#include <memory>

class Computer {
public:
    Computer() : x_(0) {}
    ~Computer() {}

private:
    int x_;
};

typedef std::shared_ptr<Computer> ComputerPtr;

void mapTest() {
    std::map<std::string, ComputerPtr> mm;
    ComputerPtr computer(new Computer);
    mm["0"] = computer;
    auto it = mm.find("1");
    // if (it->second) {
    //     int x = 0;
    // }
    return;
}

int returnZero() { return 0; }

char* returnNullptr() {
    // return NULL;
    return nullptr;
}

void mapString() {
    std::map<int, std::string> mm;
    // mm[0] = 0; // compile error
    mm[0] = returnZero();
    // mm[1] = returnNullptr(); // memory crash
    auto s = mm[0];
    // s = mm[1];
    return;
}
void intTest() {
    std::map<int, std::string> mm;
    mm[0] = "0";
    mm[1] = "1";
    mm[2] = "2";

    auto it = mm.begin();
    auto x = it->second;
    auto y = x;
}
int main() {
    mapTest();
    mapString();
    intTest();
    return 0;
}