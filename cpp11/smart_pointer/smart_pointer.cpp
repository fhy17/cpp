#include <memory>
#include <string>
#include <iostream>

// shared_ptr有几点需要注意：
//    不要用一个裸指针初始化多个shared_ptr，会出现double_free导致程序崩溃
//    通过shared_from_this()返回this指针，不要把this指针作为shared_ptr返回出来，因为this指针本质就是裸指针，通过this返回可能会导致重复析构，不能把this指针交给智能指针管理
//    尽量使用make_shared，少用new
//    不要delete get()返回来的裸指针
//    不是new出来的空间要自定义删除器
//    要避免循环引用，循环引用导致内存永远不会被释放，造成内存泄漏
struct A;
struct B;
using namespace std;
struct A {
    std::shared_ptr<B> bptr;
    ~A() { cout << "A delete" << endl; }
};

struct B {
    std::shared_ptr<A> aptr;
    ~B() { cout << "B delete" << endl; }
};

void func() {
    auto aaptr = std::make_shared<A>();
    auto bbptr = std::make_shared<B>();
    aaptr->bptr = bbptr;
    bbptr->aptr = aaptr;
    // 上面代码，产生了循环引用，导致aptr和bptr的引用计数为2，离开作用域后aptr和bptr的引用计数-1，但是永远不会为0，导致指针永远不会析构，产生了内存泄漏，如何解决这种问题呢，答案是使用weak_ptr
}

void sharedPtr() {
    std::shared_ptr<int> pointer(new int(1));

    std::shared_ptr<int> pointer1 = pointer;

    std::shared_ptr<std::string> s(new std::string("AAA"));

    std::shared_ptr<std::string> s1 = std::shared_ptr<std::string>(new std::string("AAA"));

    std::shared_ptr<std::string> p2 = std::make_shared<std::string>();

    std::shared_ptr<std::string> p3 = std::make_shared<std::string>("hello");
}

// weak_ptr
// weak_ptr是用来监视shared_ptr的生命周期，它不管理shared_ptr内部的指针，它的拷贝的析构都不会影响引用计数，纯粹是作为一个旁观者监视shared_ptr中管理的资源是否存在，
// 可以用来返回this指针和解决循环引用问题
//   返回this指针，上面介绍的shared_from_this()其实就是通过weak_ptr返回的this指针
//   解决循环引用问题
struct C;
struct D;
struct C {
    std::shared_ptr<D> bptr;
    ~C() { cout << "C delete" << endl; }
    void PrintC() { cout << "C" << endl; }
};

struct D {
    std::weak_ptr<C> aptr;  // 这里改成weak_ptr
    ~D() { cout << "D delete" << endl; }
    void PrintD() {
        if (!aptr.expired()) {  // 监视shared_ptr的生命周期
            auto ptr = aptr.lock();
            ptr->PrintC();
        }
    }
};

void funcWp() {
    auto aaptr = std::make_shared<C>();
    auto bbptr = std::make_shared<D>();
    aaptr->bptr = bbptr;
    bbptr->aptr = aaptr;
    bbptr->PrintD();
    // 输出：
    // A
    // A delete
    // B delete
}

// std::unique_ptr是一个独占型的智能指针，它不允许其它智能指针共享其内部指针，也不允许unique_ptr的拷贝和赋值。使用方法和shared_ptr类似，区别是不可以拷贝

struct F {
    ~F() { cout << "F delete" << endl; }
    void Print() { cout << "F" << endl; }
};
void funcF() {
    auto ptr = std::unique_ptr<F>(new F);
    auto tptr = std::make_unique<F>();  // error, c++11还不行，需要c++14
    // std::unique_ptr<F> tem = ptr;       // error, unique_ptr不允许移动
    ptr->Print();
}

int main() {
    sharedPtr();
    return 0;
}