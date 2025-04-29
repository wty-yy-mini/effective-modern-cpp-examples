#include <my_show_type.hpp>

class Foo {
public:
    int a{10};
    void foo() const {
        // a = 20;  // 不能对成员变量修改
        // hi();  // 只能调用常量成员函数
        foo2();  // OK
    }
    void foo2() const { cout << a << '\n'; }
    void hi() { cout << "HI" << '\n'; }
} foo;

int main() { foo.foo(); return 0; }
