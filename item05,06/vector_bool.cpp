#include <my_show_type.hpp>
#include <vector>
using std::vector;

int main() {
    vector<bool> vb(5);
    auto a = vb[0];
    PRINT_TYPE(a);  // std::_Bit_reference
    bool b = vb[0];
    PRINT_TYPE(b);  // bool
    auto c = static_cast<bool>(vb[0]);  // 强调进行了型别变换
    PRINT_TYPE(c);  // bool

    auto x = 0.9;
    PRINT_TYPE(x);  // double
    auto y = static_cast<float>(x);  // 强调进行型别变换
    PRINT_TYPE(y);  // float
    return 0;
}
