#include "thread_test.h"
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include "glog_proxy.h"
#include "thread_pool_proxy.h"

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
    ThreadZone::ThreadPool pool;
    // std::vector<std::future<std::string>> res;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    pool.setThreadCount(7);
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));

    LOG(INFO) << std::this_thread::get_id() << " begin...";
    for (auto i = 1; i <= 50; ++i) {
        if (i % 2 == 0)
            pool.commit(func1, i);
        else
            pool.commit(func2, i, std::to_string(i));

        // std::cout<<" thread count: "<<pool.threadCount() << " "<<std::endl;
        // std::cout<<"idle thread count: " << pool.idlCount() << " "
        // <<std::endl;
        // LOG(INFO) << " thread count: ", pool.threadCount(), " i: ", i, " ");
        // LOG(INFO) << "idle thread count: ", pool.idlCount(), " i: ", i, " ");
        LOG(INFO) << " thread count: " << pool.threadCount() << " idle thread: " << pool.idlCount() << " ";
    }
    // pool.setThreadCount(5);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    LOG(INFO) << "commit all ";
    std::cout << __FUNCTION__ << " commit all " << std::endl;
    LOG(INFO) << "thread count: " << pool.threadCount();
    // pool.setThreadCount(8);

    // std::cout << std::endl;
    LOG(INFO) << std::this_thread::get_id() << " end...";
    getchar();
    LOG(INFO) << "thread count: " << pool.threadCount();
}

void thread_test() {
    Work work;
    for (auto i = 1; i <= 200; ++i) {
        work.submitTask(i);
    }
    LOG(INFO) << "commit all ";
    getchar();
}

void Work::task(int x) {
    LOG(INFO) << std::this_thread::get_id() << " start... " << x;
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    LOG(INFO) << std::this_thread::get_id() << " stop";
    if (x == 50) std::cout << "function completed" << std::endl;
}

int main(int argc, char** argv) {
    InitLog(argv[0]);

    thread_test();

    threadPoolProxy();

    UninitLog();
    return 0;
}