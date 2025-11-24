#include "SimpleString.h"
#include <iostream>
using namespace std;

int main() {
    SimpleString s1;
    SimpleString s2("Hello");

    cout << "请输入一个字符串：";
    cin >> s1;

    cout << "您输入的是：" << s1 << endl;
    cout << "另一个字符串：" << s2 << endl;

    // 测试拷贝构造与赋值
    SimpleString s3 = s2;
    cout << "拷贝构造 s3 = s2: " << s3 << endl;

    s3 = s1;
    cout << "赋值 s3 = s1: " << s3 << endl;

    return 0;
}
