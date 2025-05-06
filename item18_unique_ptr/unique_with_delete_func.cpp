#include <memory>
#include <my_show_type.hpp>

// unique_ptr就是对单一指针的包装, 构造需要定义类型以及删除函数
struct Animal { virtual ~Animal() { cout << "del base animal!" << '\n'; } };

struct Cat: public Animal { ~Cat() override { cout << "del cat!" << '\n'; } };

struct Dog: public Animal { ~Dog() override { cout << "del dog!" << '\n'; } };

struct Horse: public Animal { ~Horse() override { cout << "del horse!" << '\n'; } };

void del_animal_func(Animal* ptr) {
    cout << "Call delete ptr!" << '\n';
    delete ptr;
}

auto make_animal(std::string name) {
    auto del_animal = [](Animal* ptr) {
        cout << "Call delete ptr!" << '\n';
        delete ptr;
    };
    // std::unique_ptr<Animal, decltype(del_animal)> ptr(nullptr, del_animal);
    std::unique_ptr<Animal, void (*)(Animal*)> ptr(nullptr, del_animal_func);
    if (name == "Cat") { ptr.reset(new Cat()); }
    else if (name == "Dog") { ptr.reset(new Dog()); }
    else if (name == "Horse") { ptr.reset(new Horse()); }
    else { ptr.reset(new Animal()); }
    return ptr;
}

int main() {
    {
        auto a = make_animal("Dog");  // unique指针推荐自动释放
    }  // 自动释放, 调用删除函数
    cout << "END" << "\n\n";

    auto a = make_animal("Cat");
    delete a.release();  // 手动释放, 先用release获得指针, 在对指针删除, 不会调用unique的删除函数
    cout << "\n\n";

    auto b = make_animal("Animal");
    PRINT_TYPE(b);
    // b.reset();  // 通过reset可以调用删除函数释放之前的指针
    b = make_animal("Horse");  // 或者重新复制, 会将之前的指针删除
    // 注意: 使用赋值写法时, 无法复制lambda函数, 需要用函数指针的写法
    cout << "END2!!!" << '\n';
    // 最终退出main函数也会执行释放
    return 0;
}