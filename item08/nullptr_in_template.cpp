#include <my_show_type.hpp>
template<typename FuncType, typename PtrType>
void func(FuncType& func, PtrType ptr) { func(ptr); }

void foo(int* a) { cout << "foo! " << a << '\n'; }
int* bar(int a) {
    static int value = 42;
    if (a > 0) return &value;
    return nullptr;
}

int main() {
    // 可以但是不清晰
    foo(0);
    foo(NULL);
    foo(nullptr);

    // 使用模板会直接导致报错, 仅有nullptr可行
    // func(foo, 0);  // error: invalid conversion from ‘int’ to ‘int*’
    // func(foo, NULL);  // error: invalid conversion from ‘long int’ to ‘int*’
    func(foo, nullptr);  // int*

    auto x = bar(10);
    PRINT_TYPE(x);
    PRINT_TYPE(nullptr);
    return 0;
}