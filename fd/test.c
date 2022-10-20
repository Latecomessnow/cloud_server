#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int func() {
     int fd = open("./tmp.txt", O_RDWR|O_CREAT, 0664);
     if (fd < 0) {
     return -1;
     }
     dup2(fd, 1);
     printf("hello bit");
     return 0;
   }

int main()
{
    printf("%d\n", func());
    return 0;
}
