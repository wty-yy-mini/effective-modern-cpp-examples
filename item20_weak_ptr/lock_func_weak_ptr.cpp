#include <memory>
#include <my_show_type.hpp>

int main() {
    // 可以说现有sptr再有wptr, 通过wptr来管理全部sptr的存在性
    auto sptr = std::make_shared<int>(123);
    auto wptr = std::weak_ptr<int>(sptr);
    {
        cout << sptr.use_count() << '\n';  // 1
        auto sptr2 = wptr.lock();  // 可以用weak ptr来创建shared ptr并且在多线程中保证原子性
        auto sptr3 = wptr.lock();
        auto sptr4 = wptr.lock();
        cout << sptr4.use_count() << '\n';  // 4
    }
    cout << sptr.use_count() << '\n';  // 1
    auto test_lock = [wptr]() {
        // 创建指向同一地址的shared ptr对象
        if (auto sptr2 = wptr.lock()) {
            cout << "sptr2=" << *sptr2 << '\n';
            PRINT_TYPE(sptr2);
        } else {
            cout << "Ptr is NULL" << '\n';
        }
    };
    {
        test_lock();
    }
    sptr.reset();
    test_lock();
    return 0;
}
