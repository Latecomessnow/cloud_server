#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        int cnt = 5;
        while (cnt)
        {
            printf("I am child, pid = %d, ppid = %d\n", getpid(), getppid());
            cnt--;
            sleep(1);
        }
        exit(10);
    }
    else if (id > 0)
    {
        printf("I am parent, pid = %d, ppid = %d\n", getpid(), getppid());
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if (ret > 0)
        {
            printf("exit success, exit code:%d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}
