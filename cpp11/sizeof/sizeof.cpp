#include <iostream>
#include <string>

class Test {
    int a;
    static double c;
};

class Test1 {};

class Base1 {
public:
    int data;
    virtual void play();
};
class Base2 {};
class Derive1 : public Base1 {};
class Derive2 : public virtual Base2 {};
class Derive3 : public Base1, Base2 {};

void testArr(const char str[]) { printf("%lu %lu\n", sizeof(str), strlen(str)); }
void func() {
    /*test 0*/
    char str[] = "hello";
    printf("test0 %lu %lu\n\n", sizeof(str), strlen(str));  // 6 5

    /*test 1*/
    char str1[8] = "hello";
    printf("test1 %lu %lu\n\n", sizeof(str1), strlen(str1));  // 8 5

    /**test 2*/
    char str2[] = {'h', 'e', 'l', 'l', 'o'};
    printf("test2 %lu %lu\n\n", sizeof(str2), strlen(str2));  // 5 10

    /**test 3*/
    char* str3 = "hello";
    printf("test3 %lu %lu\n\n", sizeof(str3), strlen(str3));  // 8 5

    /*test 4*/
    char str4[] = "hello";
    testArr(str4);  // 8 5

    /*test 5*/
    char str5[] = "hell\0o";
    printf("test5 %lu %lu\n", sizeof(str5), strlen(str5));  // 7 4

    /*test 6*/
    char str6[10] = {0};
    printf("test6 %lu %lu\n\n", sizeof(str6), strlen(str6));  // 10 0

    /*test 7*/
    char str7[6] = "hello";
    printf("test7 %lu %lu\n\n", sizeof(str7), strlen(str7));  // 5 10

    /*test 8*/
    char str8[5] = {0};
    strncpy(str8, "hello", 5);
    printf("%s\n", str8);  // hellohello
}

int main() {
    std::string s;
    std::cout << "sizeof(s): " << sizeof(s) << std::endl;                 // 40 跟编译器有关
    std::cout << "sizeof(string): " << sizeof(std::string) << std::endl;  // 40 跟编译器有关

    char buf[] = "hello";
    std::cout << "sizeof(buf): " << sizeof(buf) << std::endl;  // 6 数组的总字节数，包含'\0'
    std::cout << "strlen(buf): " << strlen(buf) << std::endl;  // 5 数组的总字节数，不包含'\0'

    std::cout << "sizeof(char): " << sizeof(char) << std::endl;        // 1
    std::cout << "sizeof(int): " << sizeof(int) << std::endl;          // 4
    std::cout << "sizeof(long): " << sizeof(long) << std::endl;        // 4
    std::cout << "sizeof(int64_t): " << sizeof(int64_t) << std::endl;  // 8
    std::cout << "sizeof(double): " << sizeof(double) << std::endl;    // 8

    char* pc = "123";
    std::cout << "sizeof(char*): " << sizeof(pc) << std::endl;  // 8 指针
    int* pi;
    std::cout << "sizeof(int*): " << sizeof(pi) << std::endl;  // 8 指针

    int int_arr[] = {1, 2, 4};
    std::cout << "sizeof(int[]): " << sizeof(int_arr) << std::endl;  // 12 数组的总字节数

    struct {
        char b;
        double x;
    } S;
    std::cout << "sizeof(struct S): " << sizeof(S) << std::endl;  // 16 对齐

    std::cout << "sizeof(Test): " << sizeof(Test) << std::endl;  // 4 结构或者类中的静态成员不对结构或者类的大小产生影响
    Test* ss;
    std::cout << "sizeof(ss): " << sizeof(ss) << std::endl;  // 8 ss为一个指针

    std::cout << "sizeof(Test1): " << sizeof(Test1) << std::endl;  // 没有成员变量的结构或类的大小为1

    struct MyStruct {
        char dda;
        int type;
        double dda1;
    };
    std::cout << "sizeof(MyStruct): " << sizeof(MyStruct) << std::endl;  // 16  1+3+4+8

    struct MyStruct1 {
        char dda;
        double dda1;
        int type;
    };
    std::cout << "sizeof(MyStruct1): " << sizeof(MyStruct1) << std::endl;  // 24 1+7+8+4+4

    std::cout << "sizeof(Base1): " << sizeof(Base1) << std::endl;      // 16  4+4+8
    std::cout << "sizeof(Derive1): " << sizeof(Derive1) << std::endl;  // 16  4+4+8
    std::cout << "sizeof(Derive2): " << sizeof(Derive2) << std::endl;  // 8  指向虚函数的指针
    std::cout << "sizeof(Derive3): " << sizeof(Derive3) << std::endl;  // 16  4+4+8

    func();
    return 0;
}