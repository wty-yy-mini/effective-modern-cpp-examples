#include <my_show_type.hpp>

decltype(auto) func() {
    int x = 1;
    return x;  // int ()
    // 加上括号会返回引用
    // return (x);  // int& ()
    // return ((x));  // int& ()
}

int main() {
    cout << type_id_with_cvr<decltype(func)>() << '\n';
    return 0;
}
