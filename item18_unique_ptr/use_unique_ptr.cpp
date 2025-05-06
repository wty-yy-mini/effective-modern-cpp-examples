#include <memory>  // 包含各种智能指针
#include <my_show_type.hpp>

int main() {
    auto uptr = std::make_unique<int>(123);  // 使用构造函数创建
    cout << *uptr << '\n';
    auto sptr = std::make_unique<std::string>("HI");
    cout << *sptr << '\n';
    auto sptr2 = std::make_unique<std::string>(std::move(*sptr));
    cout << sptr->size() << ' ' << sptr2->size() << '\n';
    sptr.release();  // 调用删除函数删除对象
    // cout << sptr->size();  // 运行报错: Segment fault
    return 0;
}
