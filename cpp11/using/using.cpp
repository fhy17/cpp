#include <vector>

// 使用std::bind可以将可调用对象和参数一起绑定，绑定后的结果使用std::function进行保存，并延迟调用到任何我们需要的时候。
// std::bind通常有两大作用：
//    将可调用对象与参数一起绑定为另一个std::function供调用
//    将n元可调用对象转成m(m < n) 元可调用对象，绑定一部分参数，这里需要使用std::placeholders

using vvi = std::vector<std::vector<int>>;  // c++11
using func = void (*)(int, int);
