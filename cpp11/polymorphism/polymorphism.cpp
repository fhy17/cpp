#include <iostream>
#include <string>

using namespace std;
// class A {
// public:
//     void f1() { std::cout << "f1" << std::endl; }
//     virtual void f2() { std::cout << "f2" << std::endl; }
// };

// 基类
class CBase {
    int x;

public:
    CBase(int n) { x = n; }
    ~CBase() {}
    virtual void SetX(int n) {
        x = n;
        std::cout << "CBase" << std::endl;
    }
    virtual int GetX() { return x; }
};

// 派生类
class CDerive : public CBase {
    int x;

public:
    CDerive(int n1, int n2) : CBase(n1) { x = n2; }
    ~CDerive() {}
    void SetX(int n) {
        x = n;
        std::cout << "CDerive" << std::endl;
    }
    int GetX() { return x; }
};
void func() {
    CBase *pb = new CDerive(1, 2);
    pb->SetX(3);
    pb->CBase::SetX(4);
}

class A {
public:
    A() : m_data1(0), m_data2(0) {}

    virtual void vfunc1() { cout << "A::vfunc1" << endl; };

    virtual void vfunc2() { cout << "A::vfunc2" << endl; };

    void func1() { cout << "A::func1" << endl; };

    void func2() { cout << "A::func2" << endl; };

private:
    int m_data1, m_data2;
};

class B : public A {
public:
    B() : A(), m_data3(0) {}

    virtual void vfunc1() { cout << "B::vfunc1" << endl; };

    void func1() { cout << "B::func1" << endl; };

private:
    int m_data3;
};

class C : public B {
public:
    C() : B(), m_data1(0), m_data4(0) {}

    virtual void vfunc2() { cout << "C::vfunc2" << endl; };

    void func2() { cout << "C::func2" << endl; };

private:
    int m_data1, m_data4;
};

void func1() {
    B bObject;
    A *p = &bObject;
    p->vfunc1();

    cout << "**************" << endl;

    A aObject = (A)bObject;
    aObject.vfunc1();

    cout << "**************" << endl;

    C cObject;
    p = &cObject;
    p->vfunc1();
    p->vfunc2();

    cout << "**************" << endl;

    bObject.func1();
    bObject.func2();
    bObject.A::func1();
    cObject.A::func1();
    cObject.func2();
}

int main() {
    A *a = new A;
    a->func1();
    a->vfunc1();

    A *a1 = nullptr;  // 虚函数调用需要经过虚表，没生成对象，没有虚表指针，找不到虚表，所以找不到虚函数
    a1->func1();
    // a1->vfunc1();

    // func();
    func1();
    return 0;
}