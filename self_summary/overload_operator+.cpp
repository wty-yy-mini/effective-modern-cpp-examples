#include <iostream>
#include <cstdio>
using std::cout;

class Foo {
public:
    int a{1};
    Foo() { }
    Foo(int a, int b, int c): a(a), b(b), c(c) {}
    // 重载二元运算符时, 友元函数会将this传入到低一个位置, 类似python中的self
    friend Foo operator+(const Foo& self, const Foo& other) {
        return Foo(self.a+other.a, self.b+other.b, self.c+other.c);
    }
    Foo operator*(const Foo& other) {  // 也可以不用友元函数
        return Foo(this->a*other.a, this->b*other.b, this->c*other.c);
    }
    // 友元函数可以访问类中的私有变量
    friend void friend_can_write_outside(Foo&);
    void show() { printf("%d %d %d\n", a, b, c); }

private:
    int b{2}, c{3};
};

void friend_can_write_outside(Foo& foo) {
    printf("Private b=%d, c=%d\n", foo.b, foo.c);
}

int main() {
    Foo foo, foo2;
    (foo + foo2).show(); // 2 4 6
    (foo * foo2).show(); // 1 4 9
    friend_can_write_outside(foo); // Private b=2, c=3
    return 0;
}
