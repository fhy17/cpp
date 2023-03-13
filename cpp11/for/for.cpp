#include <vector>
#include <iostream>
using namespace std;
int main() {
    vector<int> vec = {1, 2, 3, 7};
    for (auto &i : vec) {  // c++11基于范围的for循环
        cout << i << " " << endl;
    }
    return 0;
}