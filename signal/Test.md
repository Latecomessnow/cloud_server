## 信号学习笔记
这是一个测试

链接: <https://github.com/Latecomessnow/cloud_server/tree/master/signal>

added by Hui Gu

'''
pid_t waitpid(pid_t pid, int *status, int option)
'''
status中的低16位中，次低8位表示退出状态，低7位表示终止信号，第8位表示core dump标志位

​```java
class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, world!");
    }
}
​```
``` C++
#include <iostream>

using namespace std;

int main()
{
    cout << "hello world" << endl;
    return 0;
}
```