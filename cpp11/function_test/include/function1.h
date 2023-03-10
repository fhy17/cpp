#pragma once

#include <iostream>
#include <functional>
#include <memory>

using response_callback = std::function<void(int err)>;

void test1(response_callback cb) {
    if (cb) {
        cb(0);
    }
    int x = 0;
}

void testCB(int err) { std::cout << err << std::endl; }

struct Foo {
    void print_sum(int n1, int n2) { std::cout << n1 + n2 << '\n'; }
    int data = 10;
};

// 普通函数
int add(int a, int b) { return a + b; }

// lambda表达式
auto mod = [](int a, int b) { return a % b; };

// 函数对象类
class Divide {
public:
    int operator()(int denominator, int divisor) { return denominator / divisor; }
};

void functionTest() {
    test1(response_callback());
    test1(testCB);

    Foo foo;
    auto f = std::bind(&Foo::print_sum, &foo, std::placeholders::_1, std::placeholders::_2);
    f(1, 7);  // 8

    std::function<int(int, int)> a = add;
    std::function<int(int, int)> b = mod;
    std::function<int(int, int)> c = Divide();

    return;
}

#define SDLCALL __cdecl
typedef unsigned char Uint8;
typedef void(SDLCALL *SDL_AudioCallback)(void *userdata, Uint8 *stream, int len);
typedef struct SS {
    SDL_AudioCallback callback;
};

class SDL2Proxy {
public:
    SDL2Proxy(){};
    ~SDL2Proxy(){};

    // bool initAudio(SDL_AudioSpec *spec);
    // bool initVideo(int width, int height);

    static void refreshAudio(void *udata, Uint8 *stream, int len){};
    // void refreshVideo();
};

void refreshAudio(void *udata, Uint8 *stream, int len){};

class TT {
public:
    TT() { sdl_proxy_ = std::make_shared<SDL2Proxy>(); }
    void test() {
        SS spec;
        spec.callback = sdl_proxy_->refreshAudio;
        // spec.callback = std::bind(&SDL2Proxy::refreshAudio, this, std::placeholders::_1, std::placeholders::_2,
        //   std::placeholders::_3);
    }

private:
    std::shared_ptr<SDL2Proxy> sdl_proxy_;
};

int test() {
    functionTest();
    // test1();
    return 0;
}