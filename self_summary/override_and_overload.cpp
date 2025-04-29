#include <memory>

class Foo {
    /* ------------------------------ overload ------------------------------ */
    void hi();  // 相同函数名, 不同形参的型别
    void hi(int a);
    void hi(double a);
    /* ------------------------------ override ------------------------------ */
    virtual void func() const = 0;  // 如果没有=0就报错没有vtable, 因为所有virtual都需要实现
};
class Bar: public Foo {
    /* ------------------------------ override ------------------------------ */
    void func() const override final { };  // 在子类中继承重写
};
class Derived: public Bar {
    // void func() const override { };  // 不能再重写final函数了
};

int main() {
    // Foo foo;  // error: cannot declare variable ‘foo’ to be of abstract type ‘Foo’
    Foo* foo = new Bar;
    std::unique_ptr<Foo> foo2 = std::make_unique<Bar>();  // 推荐用智能指针
    Bar bar;
    return 0;
}