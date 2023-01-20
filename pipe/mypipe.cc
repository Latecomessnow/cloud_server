#include<iostream>
#include<assert.h>
#include<unistd.h>
#include<cstdio>
#include<cstring>
#include<string>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;

int main()
{
    // 1. 创建管道
    int pipefd[2] = { 0 }; // pipefd[0]--读端；pipefd[1]--写端
    // pipefd是输出型参数
    int n = pipe(pipefd);
    // debug模式下啊有效，release模式下无效
    assert(n != -1);
    // 使用一下变量n
    (void)n;

#ifdef DEBUG
    cout << "pipefd[0]:" << pipefd[0] << endl; // 3
    cout << "pipefd[1]:" << pipefd[1] << endl; // 4
#endif

    // 2. 创建子进程
    pid_t id = fork();
    assert(id != -1);
    if (id == 0)
    {
        // 子进程---读
        // 创建单向通信的信道，父进程写入， 子进程读取
        // 关闭子进程不需要的fd
        close(pipefd[1]);
        char buffer[1024];
        while (true)
        {
            ssize_t s = read(pipefd[0], buffer, sizeof(buffer) - 1);
            if (s > 0)
            {
                buffer[s] = 0;
                cout << "child get a message[" << getpid() << "] Father# " << buffer << endl;
            }
        }
        exit(0);
    }

    // 父进程---写
    // 3. 构建单向通信的信道
    // 关闭父进程不需要的fd
    close(pipefd[0]);
    string message = "我是父进程，我正在给你发消息";
    int cnt = 1;
    char send_buffer[1024];
    while (true)
    {
        // 构建一个变化的字符串
        snprintf(send_buffer, sizeof(send_buffer), "%s[%d] : %d", message.c_str(), getpid(), cnt++);
        // 写入
        write(pipefd[1], send_buffer, strlen(send_buffer));
        // 睡眠
        sleep(1);
    }

    pid_t ret = waitpid(id, nullptr, 0);
    // ret大于0就正常了，大于0通过断言
    assert(ret > 0);
    (void)ret;
    close(pipefd[1]);
    return 0;
}