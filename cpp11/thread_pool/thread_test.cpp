#include "thread_test.h"
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include "glog_proxy.h"

std::string func1(int x) {
    LOG(INFO) << std::this_thread::get_id() << "start... " << x;

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    LOG(INFO) << std::this_thread::get_id() << " stop";
    if (x == 50) std::cout << "function completed" << std::endl;
    return std::to_string(x * x) + " func1";
}

void func2(int x, std::string s) {
    //	std::cout << "---" << __FUNCTION__ << " " << std::this_thread::get_id()
    //	<< "---" << std::endl;
    LOG(INFO) << std::this_thread::get_id() << " start... " << x;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    LOG(INFO) << std::this_thread::get_id() << " stop...";
    if (x == 50) std::cout << "function completed" << std::endl;
    return;
}

void func_test() {
    ThreadPool pool;
    LOG(INFO) << std::this_thread::get_id() << " begin...";
    for (auto i = 1; i <= 50; ++i) {
        if (i % 2 == 0)
            pool.commit(func1, i);
        else
            pool.commit(func2, i, std::to_string(i));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    LOG(INFO) << "commit all ";
    std::cout << __FUNCTION__ << " commit all " << std::endl;

    LOG(INFO) << std::this_thread::get_id() << " end...";
    getchar();
}

void thread_test() {
    Work work;
    for (auto i = 1; i <= 200; ++i) {
        work.submitTask(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    LOG(INFO) << "thread_test1 commit all ";
    getchar();
}

void Work::task(int x) {
    LOG(INFO) << std::this_thread::get_id() << " start... " << x;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    LOG(INFO) << std::this_thread::get_id() << " stop";
    if (x == 200) std::cout << "function completed" << std::endl;
}

int main(int argc, char** argv) {
    InitLog(argv[0]);

    thread_test();

    UninitLog();
    return 0;
}