
#include <vector>
#include <my_show_type.hpp>

template<typename T, typename... Ts>
decltype(auto) func(Ts&&... params) {
    auto t = std::forward_as_tuple(std::forward<Ts>(params)...);
    PRINT_TYPE(t);
    PRINT_TYPE(std::get<0>(t));
    return T(std::forward<Ts>(params)...);
}

template<typename... Ts>
void foo(Ts&&... args) {
    auto t = std::forward_as_tuple(std::forward<Ts>(args)...);
    PRINT_TYPE(t);
}

int main() {
    auto v = func<std::vector<int>>(10,2);
    for (auto x: v) cout << x << '\n';
    cout << '\n';
    foo(1,2,3,1.2,3.4,std::string("abc"));
    return 0;
}
