#include<iostream>
#include<unistd.h>

using namespace std;

int main()
{
    cout << "开始执行程序代码" << endl;
    // 可变参数列表，最后一个参数要给NULL
    execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
    cout << "结束执行程序代码" << endl;
    return 0;
}
