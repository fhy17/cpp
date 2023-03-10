#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <condition_variable>
#include <mutex>

const size_t interval_time = 10;  // second

class Test {
public:
    static Test* instance() {
        static Test self;
        return &self;
    }

    bool isRunning() const { return run_; }

    void start() {
        if (!run_) {
            std::thread t([this]() {
                std::cout << "thread start" << std::endl;
                run_ = true;
                while (run_) {
                    std::cout << run_ << std::endl;
                    // std::this_thread::sleep_for(std::chrono::seconds(interval_time));
                    std::unique_lock<std::mutex> lck(mtx_);
                    cv_.wait_for(lck, std::chrono::seconds(interval_time), [this] { return !run_ || task_count_ > 0; });
                    // std::cout << run_ << std::endl;
                    --task_count_;
                }
                std::cout << "thread stop" << std::endl;
            });
            t.detach();
        }
    }

    void stop() {
        {
            std::unique_lock<std::mutex> lck(mtx_);
            run_ = false;
        }

        cv_.notify_all();
        task_count_ = 0;
    }

    void submitTask() {
        {
            std::unique_lock<std::mutex> lck(mtx_);
            ++task_count_;
        }
        cv_.notify_all();
    }

    void begin() {
        if (!run_ && !t_) {
            t_ = new std::thread([this]() {
                std::cout << "thread start" << std::endl;
                run_ = true;
                while (run_) {
                    std::unique_lock<std::mutex> lck(mtx_);
                    cv_.wait_for(lck, std::chrono::seconds(interval_time), [this] { return !run_; });
                    std::cout << run_ << std::endl;
                }
                std::cout << "thread stop" << std::endl;
            });
        }
    }

    void end() {
        run_ = false;
        cv_.notify_all();
        if (t_) {
            t_->join();
            delete t_;
            t_ = nullptr;
        }
    }

private:
    Test() : run_(false), t_(nullptr), task_count_(0) {}
    ~Test() {
        // end();
        stop();
    }

private:
    std::atomic<bool> run_;
    std::thread* t_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::atomic<size_t> task_count_;
};