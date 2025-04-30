class Foo {
public:
    Foo(double x): a(static_cast<int>(x)) { }
    explicit Foo(int x): a(x) { }
private:
    int a;
};

int main() {
    // Foo foo = 5;  // error: conversion from ‘int’ to non-scalar type ‘Foo’ requested
    Foo foo2{5};
    Foo foo3 = 5.0;  // 没有explicit可以隐式转换
    return 0;
}
