// my_show_type.hpp 用于显示模板形参的型别
#pragma once

#include <cstdio>
#include <iostream>
#include <boost/type_index.hpp>

using std::cout;
using boost::typeindex::type_id_with_cvr;

#define PRINT_TYPE(x) (cout << type_id_with_cvr<decltype(x)>() << '\n')
#define PRINT_TYPE_DIRECT(x) (cout << type_id_with_cvr<x>() << '\n')

template<typename T> void show_type_copy(T x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
template<typename T> void show_type_lref(T &x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
template<typename T> void show_type_rref(T &&x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
