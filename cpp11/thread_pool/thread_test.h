#ifndef __THREAD_TEST_H__
#define __THREAD_TEST_H__
#include "thread_pool.h"
#include <iostream>

void task_f(int x);

class Work {
public:
    void submitTask(int x) {
        // std::cout << __func__ << " " << __LINE__ << std::endl;
        pool_.commit(std::bind(&Work::task, x));
    }
    static void task(int x);

private:
    ThreadZone::ThreadPool pool_;
};

void func_test();

void thread_test();

#endif  // __THREAD_TEST_H__
