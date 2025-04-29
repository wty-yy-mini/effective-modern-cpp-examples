#include <my_show_type.hpp>

// 定义型别映射
using ll = long long;
typedef long long LL;

// 定义函数指针型别的两种方法
using func_ptr = void (*)(ll);  // 更加清晰
typedef void (*func_ptr2)(LL);  // 注意型别名称位置

void func(func_ptr f, ll a) { f(a); }
void func2(func_ptr2 f, ll a) { f(a); }
void foo(ll a) { cout << a << '\n'; }

int main() {
    func(foo, 42ll);
    func2(foo, 30ll);
}