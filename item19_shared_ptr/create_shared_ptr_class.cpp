#include <memory>
#include <vector>
#include <my_show_type.hpp>

struct AnimalSingle {
    void add_one(std::vector<std::shared_ptr<AnimalSingle>>& v) { v.emplace_back(this); }
};

void test1() {
    // auto a = AnimalSingle();  // 这是一个栈上对象, 不能用delete来删除, 需要自动释放
    auto a = new AnimalSingle();  // 在堆上创建一个对象, 这样就可以被delete释放了
    std::vector<std::shared_ptr<AnimalSingle>> v;
    a->add_one(v);
    a->add_one(v);
    a->add_one(v);
    cout << v.size() << '\n';  // 3
    for (auto& x: v) cout << x.use_count() << ' ';  // 1 1 1
    cout << '\n';
    // 最后释放会重复在一个地址释放3次, 报错
}

struct Animal: public std::enable_shared_from_this<Animal> {
    void add_one(std::vector<std::shared_ptr<Animal>>& v) {
        v.emplace_back(shared_from_this());
    }
};

void test2() {
    auto del_func = [](Animal* ptr) {
        cout << "Delete animal" << '\n';
        delete ptr;
    };
    auto a = std::shared_ptr<Animal>(new Animal(), del_func);  // 创建第一个control block, 删除函数也只能在这里声明
    // auto a = new Animal();  // 不能这样创建, 否则没有第一个control block
    std::vector<std::shared_ptr<Animal>> v;
    a->add_one(v);
    a->add_one(v);
    a->add_one(v);
    cout << v.size() << '\n';  // 3
    for (auto& x: v) cout << x.use_count() << ' ';  // 4 4 4
    cout << '\n';
}

class Animal2: public std::enable_shared_from_this<Animal2> {
public:
    static auto create() {
        auto del_func = [](Animal2* ptr) {
            cout << "Delete Animal2" << '\n';
            delete ptr;
        };
        return std::shared_ptr<Animal2>(new Animal2(), del_func);
    }
    void add_one(std::vector<std::shared_ptr<Animal2>>& v) {
        v.emplace_back(shared_from_this());
    }
private:
    Animal2() { }
};

void test3() {
    auto a = Animal2::create();  // 通过工厂函数创建, 保证有第一个control block
    std::vector<std::shared_ptr<Animal2>> v;
    a->add_one(v);
    a->add_one(v);
    a->add_one(v);
    cout << v.size() << '\n';  // 3
    for (auto& x: v) cout << x.use_count() << ' ';  // 4 4 4
    cout << '\n';
}

int main() {
    // test1();  // 直接用this创建shared_ptr, 导致创建多个control block, 释放报错
    // test2();  // 手动创建第一个control block
    test3();  // 最好的写法, 用工厂函数创建第一个control block, 把初始化函数用private保护起来, 更保险
    return 0;
}
