#pragma once

#include "thread_pool.h"
#include <iostream>

void task_f(int x);
class Work {
public:
    Work() { pool_ = std::make_shared<ThreadPool>(); }
    void submitTask(int x) {
        // std::cout << __func__ << " " << __LINE__ << std::endl;
        pool_->commit(std::bind(&Work::task, x));
    }
    static void task(int x);

private:
    std::shared_ptr<ThreadPool> pool_;
};

void func_test();

void thread_test();