#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>

#define FILE_NAME "my_fiffo"

int main()
{
    umask(0);
    int num = mkfifo(FILE_NAME, 0666);
    if (num < 0)
    {
        perror("mkfifo");
        exit(1);
    }
    return 0;
}
