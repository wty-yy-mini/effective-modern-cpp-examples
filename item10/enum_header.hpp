#pragma once
#include <my_show_type.hpp>

// 无法前置声明, 在创建时才自动推理出底层型别
// enum Color2;  // error: use of enum ‘Color2’ without previous declaration
enum Color2: int;  // 必须指定底层型别
// 可以前置声明, 默认底层型别为int
enum class Color;

void hello_color(Color x) {
    cout << "hello: " << static_cast<int>(x) << '\n';
}
