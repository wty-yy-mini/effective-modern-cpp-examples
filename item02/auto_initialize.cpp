#include <my_show_type.hpp>

int main() {
    auto x = {1, 2, 3};
    auto func = [](auto x) { cout << x.size() << '\n'; };
    func(x);  // 3
    show_type_lref(x);  // std::initializer_list<int>&
}