#include <iostream>
#include <vector>
using namespace std;

class MyVector {
public:
    int a;
    vector<int> data;

    // 移动构造函数
    MyVector(vector<int>&& other) : data(std::move(other)) {
        cout << &data << '\n';
        cout << &data[0] << ' ' << &other[0] << '\n';
        cout << data.size() << '\n';
        cout << "Move Constructor called" << endl;
    }

    MyVector(vector<int> &other): data(other) {
        cout << &data << '\n';
        cout << &data[0] << ' ' << &other[0] << '\n';
        cout << data.size() << '\n';
        cout << "GG2" << '\n';
    }

    void update(int &x) {
        a = x;
        cout << &x << ' ' << &a << '\n';
    }
};

int main() {
    vector<int> temp = {1, 2, 3, 4};
    cout << &temp << ' ' << &temp[0] << '\n';
    MyVector v(std::move(temp));  // 调用移动构造函数
    MyVector a(temp);
    int b{4};
    a.update(b);
}
