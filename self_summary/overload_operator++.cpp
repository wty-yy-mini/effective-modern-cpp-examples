#include <iostream>
using std::cout;

class Foo {
public:
    int a;
    Foo(int a=0): a(a) { }
    Foo& operator++(){ ++a; return *this; }  // 前置++
    Foo operator++(int) {  // 后置++
        Foo tmp = *this;
        ++a;
        return tmp;
    }
    void show() { cout << "a=" << a << '\n'; }
};

int main() {
    Foo foo(10);
    (foo++).show();     // a=10
    foo.show();         // a=11
    (++foo).show();     // a=12
    foo.show();         // a=12
    return 0;
}
