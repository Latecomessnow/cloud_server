#include<stdio.h>
#include<unistd.h>

int main()
{
    int a = 0;
    a++;
    execl("usr/bin/pwd", "pwd", NULL);
    printf("%d\n", a++);
    return 0;
}
