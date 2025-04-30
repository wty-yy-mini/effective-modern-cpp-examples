#include <my_show_type.hpp>

void foo(const int&) { cout << "HI! const int&" << '\n'; }
void foo(int&&) { cout << "HI! const int&&" << '\n'; }

template<typename T>
void func(T&& x, bool use_forward) { use_forward ? foo(std::forward<T>(x)) : foo(x); }

int main() {
    int a{123};
    // 使用forward保持继续传递的右值性
    func(a, true);                // HI! const int&
    func(std::move(a), true);     // HI! const int&&
    // 否则形参就是左值的
    func(a, false);               // HI! const int&
    func(std::move(a), false);    // HI! const int&
    return 0;
}
