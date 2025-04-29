#include <my_show_type.hpp>

template<typename T>
void show(T x) { PRINT_TYPE(x); }

template<> void show<double>(double x) = delete;
template<> void show<std::string>(std::string x) = delete;
template<> void show<void*>(void* x) = delete;
template<> void show<nullptr_t>(nullptr_t x) = delete;

int main() {
    int x{123};
    show(x);  // int
    show("123");  // const char*
    show(static_cast<float>(x));  // float
    // show(static_cast<double>(x));  // error: use of deleted function
    // show(std::to_string(x));  // error: use of deleted function
    // show(nullptr);  // error: use of deleted function
    show(&x);  // double*
    // show(static_cast<void*>(&x));  // error: use of deleted function
    return 0;
}
