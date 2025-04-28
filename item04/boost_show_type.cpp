#include <iostream>
#include <boost/type_index.hpp>
using std::cout;
using boost::typeindex::type_id_with_cvr;

template<class FuncType, class ValueType>
decltype(auto) call(FuncType func, ValueType value) {
    cout << type_id_with_cvr<FuncType>() << '\n';
    return func(value);
}

void hi(int a) {};

int main() {
    call(hi, 5);  // void (*)(int)
    auto a{5};
    auto* b = &a;
    char c[] = "abc";
    auto s{"abc"};
    auto& s2{"abc"};
    cout << type_id_with_cvr<decltype(a)>().pretty_name() << '\n';  // int
    cout << type_id_with_cvr<decltype(b)>() << '\n';                // int*
    cout << type_id_with_cvr<decltype(call(hi, 5))>() << '\n';      // void
    cout << type_id_with_cvr<decltype(c)>() << '\n';                // char [4]
    cout << type_id_with_cvr<decltype(s)>() << '\n';                // char const*
    cout << type_id_with_cvr<decltype(s2)>() << '\n';               // char const (&) [4]
    return 0;
}