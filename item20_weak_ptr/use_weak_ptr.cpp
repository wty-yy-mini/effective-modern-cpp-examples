#include <memory>
#include <my_show_type.hpp>

int main() {
    auto sptr = std::make_shared<int>(123);
    auto wptr = std::weak_ptr<int>(sptr);
    cout << (wptr.expired() ? "Is expired" : "unexpired") << '\n';  // unexpired
    sptr.reset();
    cout << (wptr.expired() ? "Is expired" : "unexpired") << '\n';  // Is expired
    return 0;
}
