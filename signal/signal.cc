#include<iostream>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;

void catch_signal(int sigalnum)
{
    cout << "进程捕捉到了一个信号，正在处理中：" << sigalnum << " pid:" << getpid() << endl;
}

int main()
{
    // 先注册方法，如果出现二号进程就进行回调
    // 提前设置了对特定信号的处理方法，如果没有SIGINT信号，那么catch_signal就不会被调用
    signal(SIGINT, catch_signal);

    while (true)
    {
        cout << "我是一个进程, 我正在运行... pid：" << getpid() << endl; 
        sleep(1);
    }

    return 0;
}