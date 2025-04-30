#include <my_show_type.hpp>

class Annotation {
public:
    explicit Annotation(std::string& text): value(std::move(text)) { }  // 对左值处理, const T& 是一个例外可以接收右值
    explicit Annotation(std::string&& text): value(std::move(text)) { } // 对右值处理
private:
    std::string value;
};

class Annotation2 {
public:
    explicit Annotation2(std::string& text): value(text) { }
    explicit Annotation2(std::string&& text): value(text) { }
private:
    std::string value;
};

class Annotation3 {
public:
    explicit Annotation3(std::string text): value(std::move(text)) { }  // 左右值均可处理
private:
    std::string value;
};

class Annotation4 {
public:
    explicit Annotation4(const std::string text): value(std::move(text)) { }
    // 上式等价于下式, 因为对于常量无法转为右值, 还是按照左值复制处理
    // explicit Annotation4(std::string text): value(text) { }
private:
    std::string value;
};

template<typename T>
decltype(auto) calc_time_used(int mode) {
    MyTimer timer; timer.start();
    auto s = std::string(static_cast<size_t>(1e5), 'A');
    for (int i = 0; i < static_cast<int>(1e5); ++i) {
        if (mode == 0) T a(s);
        else if (mode == 1) T a(std::string(static_cast<size_t>(1e5), 'A'));
        else if (mode == 2) {
            s = std::string(static_cast<size_t>(1e5), 'A');
            T a(s);
        }
    }
    cout << "Time used: " << timer.get_milliseconds() << "ms\n";
}

// 1. create rvalue std::string(static_cast<size_t>(1e5), 'A')
// 2. copy arg `s` to constructor param `text`
// 3. std::move to Annotation::text
// 4. copy param `text` to Annotation::text

// cmd      time_used       create_times        copy_times (s->text)    copy_times (text->Annotation::text)
// 1+3      90 ms           1e5                 0                       0
// 2+3      144 ms          0                   1e5                     0
// 3        0.9 ms          1                   0                       0
// 4        144 ms          0                   0                       1e5
// 1+4      3500 ms         1e5                 0                       1e5
// 2+4      3500 ms         1                   1e5                     1e5
// 1+2+4    3800 ms         1e5                 1e5                     1e5

int main() {
    calc_time_used<Annotation>(1);    // Time used: 90ms
    calc_time_used<Annotation3>(0);   // Time used: 144ms
    calc_time_used<Annotation>(0);    // Time used: 0.9ms
    calc_time_used<Annotation2>(0);   // Time used: 144ms
    calc_time_used<Annotation2>(1);   // Time used: 3500ms
    calc_time_used<Annotation4>(0);   // Time used: 3500ms
    calc_time_used<Annotation4>(2);   // Time used: 3800ms
    return 0;
}
