#include <my_show_type.hpp>

// void func(int) { cout << "HI int" << '\n'; }
// 这个const int定义完全没有意义和int相同, 因为按值传递会自动忽略修饰词const
// void func(const int) { cout << "HI cont int" << '\n'; }

void func(int&) { cout << "HI int&" << '\n'; }
void func(int&&) { cout << "HI int&&" << '\n'; }
// void func(const int&) { cout << "HI const int&" << '\n'; }
// void func(const int&&) { cout << "HI const int&&" << '\n'; }

// const T&&索引优先级: const T&&, const T&
// int&&索引优先级: int&&, const int&&, const int& (注意这里不能放到int&上, 如果有int其他的型别也都不存在)
// 当const T&和T&&存在时, T&&接受非const右值, cosnt T&接受除去非const右值以外的所有值(左值,const左值,const右值)

int main() {
    func(123);
    int a{123};
    func(a);
    // func(std::move(a));
    // const int b{123};
    // func(std::move(b));
    // func(b);
    return 0;
}
