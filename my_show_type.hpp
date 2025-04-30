// my_show_type.hpp 用于显示模板形参的型别
#pragma once

#include <chrono>
#include <cstdio>
#include <iostream>
#include <boost/type_index.hpp>

using std::cout;
using boost::typeindex::type_id_with_cvr;

#define PRINT_TYPE(x) (cout << type_id_with_cvr<decltype(x)>() << '\n')
#define PRINT_TYPE_DIRECT(x) (cout << type_id_with_cvr<x>() << '\n')

template<typename T>
std::string value_category(T&&) {
    // 注意这里使用了万能引用（forwarding reference）
    if constexpr (std::is_lvalue_reference<T>::value) {
        return "lvalue";
    } else if constexpr (std::is_rvalue_reference<T&&>::value) {
        return "rvalue";
    } else {
        return "unknown";
    }
}

#define CHECK_RVALUE(x) \
    std::cout << #x << " is " << value_category(x) << '\n';


template<typename T> void show_type_copy(T x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
template<typename T> void show_type_lref(T &x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
template<typename T> void show_type_rref(T &&x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }

class MyTimer {
public:
    void start() { start_time = std::chrono::high_resolution_clock::now(); }
    double get_milliseconds() {
        end_time = std::chrono::high_resolution_clock::now();
        auto duration= std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1e3;
    }
private:
    std::chrono::system_clock::time_point start_time, end_time;
};
