#include <my_show_type.hpp>

class Foo {
public:
    int a{10};
    Foo& operator++(){ ++a; return *this; }  // 前置++
    Foo operator++(int) {  // 后置++
        Foo tmp = *this;
        ++a;
        return tmp;
    }
    void hi() { cout << "hi! empty" << '\n'; }
    void hi(int a) { cout << "hi! int a" << '\n'; }
    void hi(double a) { cout << "hi! double a" << '\n'; }
    void show() { PRINT_TYPE(this); }
};

class Bar: public Foo {
public:
    // 注意: 只要子类重定义了同名函数, 所有父类函数都被隐藏, 除非用using显示引入子类
    using Foo::operator++;  // 手动引入++, 否则删除后两个++都无法找到
    Bar& operator++() = delete;  // 删除前置++
    using Foo::hi;  // 手动引入hi, 否则hi(int), hi(double)无法找到
    Bar& hi() = delete;  // 删除空形参hi
// private:  // 或者使用private隐藏函数, 也可做到相同效果
//     Bar& hi();
};

int main() {
    Bar bar;
    bar++;  // OK
    // ++bar;  // 报错, 已被删除
    // bar.hi();  // 报错
    bar.hi(1);  // hi! int a
    bar.hi(1.0);  // hi! double a
    return 0;
}
