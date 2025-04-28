#include <iostream>
#include <boost/type_index.hpp>
using std::cout;
using boost::typeindex::type_id_with_cvr;

// 模板按值传递
template<class T> void func(T x) { cout << type_id_with_cvr<decltype(x)>() << ", "; }
// 模板引用形参
template<class T> void func2(T &x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
// 模板传递数组模板
template<class T, size_t N> decltype(auto) arraySize(T (&s)[N]) { return N; }

void call_func(void (&f)()) { f(); }  // 指定的函数引用
template<size_t N>  // 
void show_array_size(char (&s)[N]) { cout << "array=" << s << ", size=" << N << '\n'; }

void foo() { cout << "foo!" << '\n'; }
void bar(int a) { cout << "bar!" << '\n'; }

int main() {
    auto a = 1;
    func(foo), func2(foo);  // void (*)(), void (&)()
    call_func(foo);  // foo!
    // call_func(bar);  // 报错
    func(bar), func2(bar);  // void (*)(int), void (&)(int)
    char s[] = "abc123def";
    cout << type_id_with_cvr<decltype(s)>() << '\n';  // char [10]
    func(s), func2(s);  // char*, char (&) [10]
    show_array_size(s);  // array=abc123def, size=10
    const char* const ptr = s;
    func(ptr), func2(ptr);  // char const*, char const* const
    cout << arraySize(s) << '\n';  // 10
    // cout << arraySize(ptr) << '\n';  // 报错
    return 0;
}