#include <my_show_type.hpp>

// 除非需要引用时用decltype(auto), 否则用auto即可
decltype(auto) func() {
    static int x = 1;
    return (x);  // int ()
    // 加上括号会返回引用
    // return (x);  // int& ()
    // return ((x));  // int& ()
}

auto func2() {
    int x = 1;
    return x;
}

int main() {
    cout << type_id_with_cvr<decltype(func)>() << '\n';
    PRINT_TYPE(func);  // int& ()
    PRINT_TYPE(func2); // int ()
    return 0;
}
