#include <my_show_type.hpp>
#include <vector>

class First {
    public:
    First(int a) { cout << "init 1-1" << '\n'; }
};

class Second {
    public:
    Second(int a, int b) { cout << "init 2-1" << '\n'; }
    // 如果存在可转换数据类型的std::initializer_list, 大括号就一定会调用该函数
    Second(std::initializer_list<int> x) { cout << "init 2-2" << '\n'; }
    Second(std::string a, int b) { cout << "init 2-3" << '\n'; }
};

class Third {
    public:
    Third(std::string a, float b) { cout << "init 3-1" << '\n'; }
    Third(std::initializer_list<std::string> x) { cout << "init 3-2" << '\n'; }
};

int main() {
    First a(4.0);  // init 1-1
    // First a2{4.0};  // 报错, 无法进行窄化变化(narrowing conversion), 从double->int会损失精度
    First a2{static_cast<int>(4.0)};  // init 1-1
    First a3(true);  // init 1-1, bool -> int不会丢失精度

    Second b(1, 2);  // init 2-1
    // 存在转化为initializer_list<int>可能, 则会优先
    Second b2{1, 2};  // init 2-2, 存在可能就会调用形参为initializer_list
    Second b3{"HI", 2};  // init 2-3
    // 存在转为initializer_list<int>可能, 但是需要将double->int, 由于无法窄化变换, 报错
    // Second b4{1.0, 2};

    Third c{"HI", 1};  // init 3-1, 不存在转为initializer_list<std::string>可能
    Third c2{"HI", 1.0};  // init 3-1, 从double变化到float不算窄化
    Third c3{"HI", "OK"};  // init 3-2

    std::vector<int> v{10, 20};  // 使用了initializer_list创建方法
    cout << v.size() << '\n';  // 2
    std::vector<int> v2(10, 20);  // 创建了长度为10, 每个值都是20的vector
    cout << v2.size() << '\n';  // 10
    return 0;
}