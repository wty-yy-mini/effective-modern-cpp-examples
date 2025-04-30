#include <memory>
#include <my_show_type.hpp>

class Widget {
public:
    int* a;
    int val;
    Widget(const int& x) { val = x; a = &val; }
    Widget(int&& x) { a = &x; }
};

// class Widget {  // 使用智能指针无法做到
// public:
//     std::unique_ptr<int> a;
//     Widget(const int& x) { a = std::make_unique<int>(int(x)); }
//     Widget(int&& x) { a = std::make_unique<int>(x); }
// };

int main() {
    int a = 10;
    Widget w(a);  // 左值复制
    *w.a = 20;
    cout << a << ' ' << *w.a << '\n';  // 10 20
    Widget w2(std::move(a));  // 转为右值传入移动
    *w2.a = 20;
    cout << a << ' ' << *w2.a << '\n';  // 20 20
    return 0;
}
