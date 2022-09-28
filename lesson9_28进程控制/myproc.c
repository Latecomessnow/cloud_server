#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        // child
        int cnt = 5;
        while (cnt)
        {
            printf("I am child:%d\n", cnt--);
            sleep(1);
        }
        exit(10); // only test
    }
    else
    {
        // parent
       int status = 0;
       // 默认是在阻塞状态去等待子进程状态变化(就是退出!)
       // options 默认为0，代表阻塞等待, WNOHANG:非阻塞式等待
       pid_t ret = waitpid(id, &status, 0);// 只有子进程退出的时候，父进程才会调用waitpid函数进行返回
       if (ret > 0)
       {
           // id > 0 等待指定进程退出
           // id == 0
           // id == -1 等待任意一个子进程退出
           printf("Parent waits for success. exit code:%d, exit signal:%d\n", (status >> 8) & 0xFF, status & 0x7F);
           if (WIFEXITED(status))
           {
               // 子进程是正常退出的
               printf("子进程执行完毕, 子进程的退出码:%d\n", WEXITSTATUS(status));
           }
           else
           { 
               printf("子进程异常退出, %d\n", WIFEXITED(status));
           }
       }
         
    }
    return 0;
}
