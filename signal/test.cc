#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

using namespace std;

// int main()
// {
//     cout << "I'm running..." << endl;
//     // 三秒后发生除零错误，程序崩溃
//     sleep(10);
//     int a = 10 / 0;
//     return 0;
// }

// int main()
// {
//     if (fork() == 0)
//     {
//         // child
//         cout << "I'am running..." << endl;
//         int* p = nullptr;
//         *p = 100;
//         // 退出子进程,观察core dump标志位
//         exit(0);
//     }
//     int status = 0;
//     pid_t id = wiatpid()
//     return 0;
// }

//////////////////////////////////////////////

int main()
{
     // fork创建子进程成功后,父进程返回子进程的pid,子进程返回0
     // fork函数存在两个返回值
     pid_t id = fork();
     if (id == 0)
     {
          // child
          cout << "I'm child, running..." << endl;
          cout << "pid:" << getpid() << " "
               << "ppid:" << getppid() << endl;
          int *p = nullptr;
          *p = 100;
          // 退出子进程,观察core dump标志位
          //exit(0);
     }
     else
     {
          cout << "I'm father, running..." << endl;
          cout << "pid:" << getpid() << " "
               << "ppid:" << getppid() << endl;
          int status = 0;
          // 父进程返回的pid正是紫禁城的pid,所以可以直接在waitpid等待子进程
          pid_t change = waitpid(id, &status, 0);
          // 退出码, core dump标志位, 退出信号
          cout << "ExitCode:" << ((status >> 8) & 0xff) << endl
               << "core dump:" << ((status >> 7) & 1) << endl
               << "ExitSignal:" << (status & 0x7f) << endl;
            cout << "exit:" << WIFEXITED(status) << endl;
     }
     return 0;
}

