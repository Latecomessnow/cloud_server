#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>

using namespace std;

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        int cnt = 5;
        while (cnt)
        {
            printf("I am child process:%d\n", cnt--);
            sleep(1);
        }
    }
    else 
    {
        int status = 0;
        pid_t res = waitpid(-1, &status, 0); // 阻塞式等待
        if (res > 0)
        {
            printf("等待子进程成功，退出码:%d\n", WEXITSTATUS(status));
        }
    }
}
