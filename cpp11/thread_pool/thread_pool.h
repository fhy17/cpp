#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <future>
#include <functional>
// #include <iostream>

class ThreadPool {
public:
    ThreadPool() : run_(true), thread_count_(std::thread::hardware_concurrency()) {
        // std::cout << thread_count_ << std::endl;
        increaseThread(thread_count_);
    }
    ~ThreadPool() {
        run_ = false;
        task_cv_.notify_all();
        for (std::thread& t : pool_) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    template <class F, class... Args>
    auto commit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        if (!run_) throw std::runtime_error("commit on ThreadPool is stopped.");
        using RetType = decltype(f(args...));
        auto task =
            std::make_shared<std::packaged_task<RetType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<RetType> future = task->get_future();
        {
            std::lock_guard<std::mutex> lock{lock_};
            tasks_.emplace([task]() { (*task)(); });
        }
        task_cv_.notify_one();
        return future;
    }

private:
    void increaseThread(size_t size) {
        while (pool_.size() < thread_count_) {
            pool_.emplace_back([this] {
                while (run_) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lck(lock_);
                        task_cv_.wait(lck, [this] { return !run_ || !tasks_.empty(); });
                        if (!run_ && tasks_.empty()) {
                            return;
                        }
                        task = move(tasks_.front());
                        tasks_.pop();
                    }
                    task();
                }
            });
        }
    }

private:
    using Task = std::function<void()>;
    std::vector<std::thread> pool_;
    std::queue<Task> tasks_;
    std::mutex lock_;
    std::condition_variable task_cv_;
    std::atomic<bool> run_;
    size_t thread_count_;
};