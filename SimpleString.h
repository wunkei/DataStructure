#ifndef SIMPLE_STRING_H
#define SIMPLE_STRING_H

#include <iostream>
#include <cstring>

class SimpleString {
private:
    char* data;   // 内容
    int length;   // 长度

public:

    // 构造函数
    SimpleString(const char* str = "") {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    // 拷贝函数
    SimpleString(const SimpleString& other) {
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    // 运算符
    SimpleString& operator=(const SimpleString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // 析构函数
    ~SimpleString() {
        delete[] data;
    }

    // 获取长度
    int size() const {
        return length;
    }

    // 输出
    friend std::ostream& operator<<(std::ostream& out, const SimpleString& s) {
        out << s.data;
        return out;
    }

    // 输入
    friend std::istream& operator>>(std::istream& in, SimpleString& s) {
        char temp[1000];
        in >> temp;

        delete[] s.data;
        s.length = strlen(temp);
        s.data = new char[s.length + 1];
        strcpy(s.data, temp);

        return in;
    }
};

#endif
