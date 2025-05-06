#include <memory>  // 包含各种智能指针
#include <my_show_type.hpp>

struct Animal {
    std::string name;
    Animal(std::string name): name(name) { }
    ~Animal() { cout << "Destruct: " << name << '\n'; }
};

void del_func2(Animal* ptr) {
    cout << "Call delete func2!\n";
    delete ptr;
}

int main() {
    {
    // 两种创建智能指针的方法, 在无需制定删除函数时, 优先使用make_unique
    auto uptr = std::make_unique<Animal>("Dog");
    auto uptr2 = std::unique_ptr<Animal>(new Animal("Cat"));
    // 调用指针方法和普通指针没有区别
    cout << "Unique point animal name: " << uptr->name << '\n';
    }  // 从栈上删除uptr, uptr2, 输出两个(先析构Cat) "Destruct: Cat", "Destruct: Dog"

    // 自定义lambda删除函数
    auto del_func = [](Animal* ptr) {
        cout << "Call delete function!\n";
        delete ptr;
    };
    auto uptr3 = std::unique_ptr<Animal, decltype(del_func)>(new Animal("Horse"), del_func);
    // uptr3.release();  // 将uptr3中的指针以裸指针返回, 该UniquePtr不再对其进行管理
    uptr3.reset();  // 将uptr3中的指针删除, 可重置为另一个Animal*
    // 删除指针时调用del_func, 输出 "Call delete function!", 再调用析构函数

    // 自定义删除函数 (函数指针)
    auto uptr4 = std::unique_ptr<Animal, void (*)(Animal*)>(new Animal("Piggy"), del_func2);
    auto uptr5 = std::unique_ptr<Animal, decltype(&del_func2)>(new Animal("Fox"), del_func2);
    uptr4.reset();  // 调用删除函数del_func2
    uptr5.reset();  // 调用删除函数del_func2
    cout << "END\n";
    return 0;
}
