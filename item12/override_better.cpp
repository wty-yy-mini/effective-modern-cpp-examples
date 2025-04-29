#include <vector>
#include <memory>
#include <my_show_type.hpp>

class Foo {
public:
    using data_type = std::vector<double>;
    virtual void f() const { cout << "HI Foo" << '\n'; }
    virtual data_type& get() = 0;
    virtual data_type& get_v() & = 0;
    virtual data_type get_v() && = 0;
protected:
    data_type v{1,2,3};
};

class Bar: public Foo {
public:
    void f() const override { cout << "HI Bar" << '\n'; }
    data_type& get() override { return v; }
    data_type& get_v() & override { printf("Call Left\n"); return v; }
    data_type get_v() && override { printf("Call right\n"); return std::move(v); }
};

Foo::data_type* get_rv(bool use_get=true) {
    using dt = Foo::data_type;
    dt* ret;
    if (use_get) {
        auto rv = Bar().get();
        ret = &rv;  // 由于是右值, 出if作用域就会被释放, 产生悬空指针
        printf("get_rv in use_get {}, values=");
        for (auto x: *ret) cout << x << ' '; cout << '\n';
    }
    else {
        static auto v = Bar().get_v();  // Call right
        ret = &v;
    }
    printf("get_rv return, values=");
    for (auto x: *ret) cout << x << ' '; cout << '\n';
    return ret;
}

/* ------------------ 使用智能指针由于将右值拷贝, 所以没有问题 ------------------- */
std::unique_ptr<Foo::data_type> get_rv_smart_ptr() {
    using dt = Foo::data_type;
    std::unique_ptr<dt> ret;
    auto rv = Bar().get();
    ret = std::make_unique<dt>(rv);  // 将右值拷贝一份, ret指向拷贝后的地址
    printf("get_rv_smart_ptr in use_get {}, values=");
    for (auto x: *ret) cout << x << ' '; cout << '\n';
    return ret;
}

int main() {
    std::unique_ptr<Foo> foo = std::make_unique<Bar>();
    foo->f();  // HI Bar, 调用子类重写后的函数
    auto v = foo->get_v();  // Call Left, 纯虚函数, 使用子类重写的函数
    cout << v.size() << '\n';  // 3
    putchar('\n');

    auto rv = get_rv(true);  // 获取右值指针
    for (auto x: *rv) cout << x << ' ';  // 输出乱码
    cout << "\n\n";

    rv = get_rv(false);  // 通过声明全局变量所以正确
    for (auto x: *rv) cout << x << ' ';  // 1 2 3
    cout << "\n\n";

    auto rv_smart = get_rv_smart_ptr();  // 通过智能指针返回默认拷贝所以正确
    for (auto x: *rv_smart) cout << x << ' ';  // 1 2 3
    cout << "\n";
    return 0;
}
