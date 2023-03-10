#pragma once

#include <iostream>
#include <memory>
#include <functional>

class Test {
public:
    using response_callback = std::function<void(int err, const char* hdr, const char* body, int body_len)>;

    static Test* instance() {
        static Test self;
        return &self;
    }

    void test(const char* data, response_callback cb) {
        std::cout << "test " << data << std::endl;
        std::string body = "body";
        cb(0, nullptr, body.c_str(), body.length());
    }

private:
    Test() {}
    ~Test() {}
};

struct ActivateBase {
    using on_response = std::function<void(const char* hdr, const char* body, int body_len, int cashier_id)>;

public:
    ActivateBase() {}
    virtual ~ActivateBase() {}

public:
    // void set_cashier_info(int cashier_id, int sid);
    void bind_response(on_response resp) { resp_cb_ = resp; }

protected:
    // void i_send_response(int cmdid, const std::string& data);
    // bool i_check_authority(CASHIER_OPER_TYPE cot, const std::string& remark = std::string());

protected:
    on_response resp_cb_;
    int cashier_id_;
    bool authed_;
    int sid_;
};

struct Activate : public std::enable_shared_from_this<Activate>, ActivateBase {
public:
    Activate() {}
    ~Activate() {}

public:
    void activate(const char* req, int len, int authed) {
        auto shared_this = shared_from_this();
        std::string body = "active";
        resp_cb_(nullptr, body.c_str(), body.length(), 0);
    }
};

class Proxy : public std::enable_shared_from_this<Proxy> {
public:
    Proxy() = default;
    ~Proxy() = default;

    void place_order(int x, int& y) {
        auto shared_this = shared_from_this();
        auto fo = [shared_this, this, &y](int err) {
            std::cout << "fo err " << err << ", y " << ++y << std::endl;
            std::cout << std::endl;
        };

        auto active_fo = [shared_this, this, &x, &fo, &y]() {
            std::shared_ptr<Activate> cmd = std::make_shared<Activate>();
            cmd->bind_response(
                [shared_this, this, &fo, &x, &y](const char* hdr, const char* body, int body_len, int cashier_id) {
                    std::cout << body << ", " << body_len << ", y " << ++y << std::endl;
                    fo(x);
                });

            std::string data = "123";
            cmd->activate(data.c_str(), data.length(), 0);
        };

        const char* data = "1234567";
        Test::instance()->test(
            data, [shared_this, this, &active_fo, &y](int err, const char* hdr, const char* body, int body_len) {
                std::cout << "Test::instance()->test err: " << err << ", y " << ++y << std::endl;
                active_fo();
            });
    }
};

class Test1 : public std::enable_shared_from_this<Test1> {
public:
    void activate(const char* req, int len, int authed) {
        auto shared_this = shared_from_this();
        std::string body = "active";
    }

    Test1() {}
    ~Test1() {}
};

class TestProxy {
public:
    static TestProxy* instance() {
        static TestProxy self;
        return &self;
    }

    void activate(const char* req, int len, int authed) { ptr_->activate(req, len, authed); }

private:
    TestProxy() { ptr_ = std::make_shared<Test1>(); }
    ~TestProxy() {}
    std::shared_ptr<Test1> ptr_;
};