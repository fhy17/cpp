#pragma once
#include <functional>

using err_cb = std::function<void(int err, std::string order_number)>;

typedef struct OrderInfo {
    err_cb cb;
    time_t bind_time;
    int cashier_id;
    int authed;
    std::string order_id;
} OrderInfo;

void cb_test(std::string& order_id, err_cb cb) {
    if (cb) {
        cb(0, order_id);
    }
}

void func_cb() {
    OrderInfo oi;
    oi.order_id = "7";
    cb_test(oi.order_id, oi.cb);
    err_cb cb = [](int err, std::string on) {
        int x = err;
        std::string s = on;
    };
    cb_test(oi.order_id, cb);
}