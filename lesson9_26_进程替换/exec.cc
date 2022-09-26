#include<iostream>
#include<unistd.h>
#include<stdio.h>

using namespace std;

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        cout << "I am child, pid:" << getpid() << ", ppid:" << getppid() << endl;
        execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
        cout << "hello world" << endl;
    }
    else if (id > 0)
    {
        cout << "I am parent, pid:" << getpid() << ", ppid:" << getppid() << endl;
    }
    else 
    {
        perror("fork fail");
    }
    return 0;
}
