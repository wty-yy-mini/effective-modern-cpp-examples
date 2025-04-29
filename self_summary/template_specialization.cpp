#include <my_show_type.hpp>

template<typename T>
void func(T x) { cout << "HI! "; PRINT_TYPE(x); }

template<>
void func<bool>(bool x) { cout << "HI! You are bool!" << '\n'; }

template<typename T>
void func(T* x) { cout << "HI ptr! "; PRINT_TYPE(x); }

template<>
void func<bool>(bool* x) { cout << "HI ptr! You are bool ptr!" << '\n'; }

int main() {
    int x = 10;
    bool flag = false;
    func(x);
    func(true);
    func(&x);
    func(&flag);
    return 0;
}
