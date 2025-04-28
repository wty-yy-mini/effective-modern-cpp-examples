// my_show_type.hpp 用于显示模板形参的型别
#pragma once

#include <iostream>
#include <boost/type_index.hpp>
using std::cout;
using boost::typeindex::type_id_with_cvr;

template<class T> void show_type_copy(T x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
template<class T> void show_type_lref(T &x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
template<class T> void show_type_rref(T &&x) { cout << type_id_with_cvr<decltype(x)>() << '\n'; }
