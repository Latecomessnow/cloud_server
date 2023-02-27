//#include<iostream>
//#include<signal.h>
//#include<sys/types.h>
//#include<unistd.h>
//
//using namespace std;
//
//void catch_signal(int sigalnum)
//{
//    cout << "进程捕捉到了一个信号，正在处理中：" << sigalnum << " pid:" << getpid() << endl;
//}
//
//int main()
//{
//    // 先注册方法，如果出现二号进程就进行回调
//    // 提前设置了对特定信号的处理方法，如果没有SIGINT信号，那么catch_signal就不会被调用
//    signal(SIGINT, catch_signal);
//
//    while (true)
//    {
//        cout << "我是一个进程, 我正在运行... pid：" << getpid() << endl; 
//        sleep(1);
//    }
//
//    return 0;
//}


#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

// 对信号进行自定义行为，这样2好信号默认的终止进程就不会执行，而是执行handler方法
void handler(int sig)
{
    cout << endl << "The process received a signal:" << sig << endl;
}

int main()
{
    // signal接口的第一个参数是信号的参数，如几号信号
    // 第二个参数是一个回调函数，这个回调函数的返回值是void，参数是int，标识接收到了几号信号
    signal(SIGINT, handler);
    while (1)
    {
        cout << "hello horld" << endl;
        sleep(1);
    }
    return 0;
}
