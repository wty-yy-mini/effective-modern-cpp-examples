#include <my_show_type.hpp>

int main() {
    std::string a{"abcd"};
    cout << a.size() << '\n';  // 4
    auto b{std::move(a)};
    cout << a.size() << '\n';  // 0
    cout << b.size() << '\n';  // 4
    return 0;
}
