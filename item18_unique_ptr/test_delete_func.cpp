#include <memory>
#include <my_show_type.hpp>

// unique_ptr就是对单一指针的包装, 构造需要定义类型以及删除函数
struct Animal { virtual ~Animal() { cout << "del base animal!" << '\n'; } };

struct Dog: public Animal { ~Dog() override { cout << "del dog!" << '\n'; } };

int main() {
    Animal* dog = new Dog();  // 加上虚函数的析构函数, 保证删除可以删掉dog中内容
    delete dog;
    return 0;
}