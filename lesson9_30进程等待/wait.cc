#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<vector>

using namespace std;

// 函数指针类型
typedef void (*handler_t)();

vector<handler_t> handlers;

void fun_one()
{
    printf("这是一个临时任务1\n");
}

void fun_two()
{

    printf("这是一个临时任务2\n");
}


void Load()
{
    handlers.push_back(fun_one);
    handlers.push_back(fun_two);
}

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        int cnt = 5;
        while (cnt)
        {
            printf("I am child:%d\n", cnt--);
            sleep(1);
        }
        exit(11);
    }
    int quit = 1;
    while (quit)
    {
        int status = 0;
        pid_t ret = waitpid(-1, &status, WNOHANG);
        if (ret > 0)
        {
            printf("父进程等待成功，子进程已退出，退出码:%d\n", status);
            quit = 0;
        }
        else if (ret == 0)
        {
            printf("父进程等待成功，子进程还没有退出，父进程可以先去干其他事\n");
            if (handlers.empty())
                Load();
            for (auto e : handlers)
            {
                e();
            }
        }
        else
        {
            printf("父进程等待失败\n");
            quit = 0;
        }
        sleep(1);
    }
    return 0;
}
