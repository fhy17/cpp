#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <thread>
#include <functional>

std::string g_id = "123";
class PlaceOrder : public std::enable_shared_from_this<PlaceOrder> {
public:
    using response_callback = std::function<void(std::string id)>;
    typedef struct OrderInfo {
        response_callback cb;
        // std::string param;
        time_t bind_time;
    } OrderInfo;

    static PlaceOrder* instance() {
        static PlaceOrder self;
        return &self;
    }

    void bind(response_callback cb, std::string id /*, const std::string& param*/) {
        order_info_[id] = OrderInfo{cb /*, param*/, time(0)};
    }

    void call(std::string id) {
        auto it = order_info_.find(id);
        if (it != order_info_.end()) {
            it->second.cb(id);
            order_info_.erase(it);
        }
    }

private:
    PlaceOrder() {}
    ~PlaceOrder() {}

private:
    std::map<std::string, OrderInfo> order_info_;
};

class place_order_cmd_t : public std::enable_shared_from_this<place_order_cmd_t> {
public:
    place_order_cmd_t() = default;
    ~place_order_cmd_t() = default;

    void place_order(const char* req, int len, int authed) {
        auto shared_this = shared_from_this();
        std::string id = g_id;
        PlaceOrder::instance()->bind(
            [this](std::string id) {
                std::cout << "callback id: " << id << std::endl;
                std::cout << "thread id " << std::this_thread::get_id() << std::endl;
            },
            id);
    }
};

void func1() {
    std::thread t([]() {
        std::cout << "func 1, thread id: " << std::this_thread::get_id() << std::endl;
        auto place_order = PlaceOrder::instance();

        std::shared_ptr<place_order_cmd_t> cmd = std::make_shared<place_order_cmd_t>();
        cmd->place_order(nullptr, 0, 0);
        std::cout << "func 1 thread end" << std::endl;
    });
    t.detach();
}

void func2() {
    std::thread t([]() {
        std::cout << "func 2, thread id " << std::this_thread::get_id() << std::endl;
        PlaceOrder::instance()->call(g_id);

        std::cout << "func 2 thread end" << std::endl;
    });
    t.detach();
}

void func3() {
    std::thread t([]() {
        std::cout << "func 3, thread id " << std::this_thread::get_id() << std::endl;
        PlaceOrder::instance()->call("0");

        std::cout << "func 3 thread end" << std::endl;
    });
    t.detach();
}

int main() {
    std::cout << "thread id " << std::this_thread::get_id() << std::endl;
    func1();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    func3();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    func2();
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}