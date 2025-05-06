#include <memory>
#include <my_show_type.hpp>

int main() {
    auto del_func = [](int* ptr) {
        cout << "Call delete func!" << '\n';
        delete ptr;
    };
    // 构建带有删除函数的, 无法使用make_shared
    // 注意: shared_ptr类型中不和删除函数绑定, 这与unique_ptr不同
    {
        std::shared_ptr<int> sptr(new int(8), del_func);
        cout << sptr.use_count() << '\n';
        {
            std::shared_ptr<int> sptr2(sptr);  // sptr2和sptr共用相同的control block
            cout << sptr.use_count() << ' ' << sptr2.use_count() << '\n';  // 2 2
        }  // 自动删除sptr2, use_count -= 1
        cout << "sptr.unique=" << (sptr.unique() ? "True" : "False") << '\n';  // 判断是否是唯一的
        // sptr.reset();  // reset同样会释放指针, 当use_count=0时, 会自动释放
        cout << "RESET" << '\n';
    }  // 当use_count=0时, 调用删除函数
    cout << "END!!!" << '\n';

    // 也可以使用make_shared通过构造函数创建, 使用默认删除函数
    auto sptr = std::make_shared<int>(123);

    {
        // 不推荐创建裸指针, 不要对同一指针创建两个control block, 否则可能被重复删除两次, 导致未定义错误
        auto ptr = new int(8);
        sptr = std::shared_ptr<int>(ptr);  // 使用shared_ptr可以从指针构建
        // auto sptr2 = std::shared_ptr<int>(ptr);  // 产生两个control block
        // cout << sptr.use_count() << ' ' << sptr2.use_count() << '\n';  // 1 1
    }  // 在退出时, ptr会被连续释放两次, 导致报错!


    return 0;
}
