#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;
    size_t length;

public:
    // 1. 默认构造
    MyString() {
        // 你的代码：初始化为空字符串
        data = nullptr;
        length = 0;
    }

    // 2. 带参构造
    MyString(const char* str) {
        // 你的代码：分配内存并拷贝 str
		
		}
    }

    // 3. 析构函数
    ~MyString() {
        // 你的代码：释放内存
        delete[] data;
    }
    }

    // 4. 拷贝构造
    MyString(const MyString& other) {
        // 你的代码：深拷贝
           
    }

    // 5. 拷贝赋值
    MyString& operator=(const MyString& other) {
        // 你的代码：处理自我赋值、释放旧内存、分配新内存
        return *this;
    }

    // 6. 移动构造
    MyString(MyString&& other) noexcept {
        // 你的代码：转移所有权，将 other 置空
    }
};

int main() {
    // 在这里写测试代码，比如：
    // MyString s1("Hello");
    // MyString s2 = s1; // 拷贝构造
    // MyString s3 = std::move(s1); // 移动构造
    // 看看会不会崩溃
    return 0;
}