#include <iostream>
#include <functional>
#include <thread>

class Base {
public:
    using on_response = std::function<void(int cashier_id)>;
    void bind_response(on_response resp) { resp_cb_ = resp; }

protected:
    on_response resp_cb_;
};

class Cmd : std::enable_shared_from_this<Cmd>, public Base {
public:
    Cmd() {}
    ~Cmd() {}

    void test(int &cashier_id) {
        if (resp_cb_) resp_cb_(cashier_id);
    }
};

void functionCall(int thread_id, int &cashier_id, bool flag = false) {
    auto out = [&flag, thread_id](int cashier_id) {
        auto s = flag ? "true" : flag;
        std::cout << "out flag: " << s << ", cashier id: " << cashier_id << ", thread_id: " << thread_id << std::endl;
    };
    std::shared_ptr<Cmd> cmd = std::make_shared<Cmd>();
    cmd->bind_response([&flag, &out, thread_id](int cashier_id) {
        auto s = flag ? "true" : flag;
        std::cout << "flag: " << s << ", cashier id: " << cashier_id << ", thread_id: " << thread_id << std::endl;
        out(cashier_id);
    });
    cmd->test(cashier_id);
}

int main() {
    std::cout << "lambda test" << std::endl;
    // auto cashier_id = 7;
    std::thread t([]() {
        auto count = 0;
        auto cashier_id = 7;
        while (++count < 10) {
            // cashier_id = 7;
            functionCall(0, cashier_id);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    std::thread t1([]() {
        auto count = 0;
        auto cashier_id = 1;
        while (++count < 10) {
            // cashier_id = 1;
            functionCall(1, cashier_id, true);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    t.join();
    t1.join();
    return 0;
}