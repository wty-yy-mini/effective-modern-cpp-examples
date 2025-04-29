#include <map>
#include <vector>
#include <my_show_type.hpp>
using std::map;
using std::vector;

template<typename T>  // 通过构造struct, 将别名赋值到type上
struct MyMap {
    typedef map<T, std::vector<T>> type;
};

template<typename T>  // 使用时需引用::type并声明为typename
struct Foo { typename MyMap<T>::type mp; };

int main() {
    Foo<int> foo;
    foo.mp[4] = {1,2,3,4};
    foo.mp[1] = {3,4};
    for (auto x : foo.mp) {
        cout << "key=" << x.first << ", value=";
        PRINT_TYPE(x.second);
        for (auto y : x.second) { cout << y << ' '; }
        cout << '\n';
    }
    return 0;
}

/* --------------------------------- Return ---------------------------------
key=1, value=std::vector<int, std::allocator<int> >
3 4 
key=4, value=std::vector<int, std::allocator<int> >
1 2 3 4 
-------------------------------------------------------------------------- */
