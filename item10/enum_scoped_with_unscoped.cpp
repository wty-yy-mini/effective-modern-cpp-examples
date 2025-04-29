#include <enum_header.hpp>
#include <my_show_type.hpp>

enum class Color { red, white, black };
enum Color2: int { red, white, black };  // 底层型别需和声明一致

// 默认的enum class类型为int最大到0x7fffffff
enum class Status { foo=100, bar=0x7fffffff };
// 指定enum class类型
enum class Status2: uint64_t { bar=0xffffffffffffffff };
// 不限范围枚举可以自动推理底层型别的, 这意味着修改Status3就需要重新编译整个代码
enum Status3 { bar=0xffffffffffffffff };

int main() {
    cout << red << '\n';  // 0
    // 注意限定作用域枚举必须强制转化类型
    cout << static_cast<int>(Color::red) << '\n';  // 0
    PRINT_TYPE(Color::red);  // Color
    PRINT_TYPE(red);  // Color2
    hello_color(Color::red);  // hello: 0, 调用前置声明中的函数
    // 查看底层型别
    PRINT_TYPE_DIRECT(std::underlying_type_t<Color>);  // int
    PRINT_TYPE_DIRECT(std::underlying_type_t<Status2>); // unsigned long
    PRINT_TYPE_DIRECT(std::underlying_type_t<Status3>); // unsigned long
    return 0;
}