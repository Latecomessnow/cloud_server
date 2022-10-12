#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main()
{
    const char* str = "I like linux";
    char buffer[60];
    memset(buffer, '\0', sizeof(buffer));
    printf("stdin: %d\n", stdin->_fileno);
    printf("stdout: %d\n", stdout->_fileno);
    printf("stderr: %d\n", stderr->_fileno);
    umask(0);
    // rw-rw-rw
    int fd = open("hello.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("open error");
        return 1;
    }
    else 
        printf("open success\n");
    write(fd, str, strlen(str));
    close(fd);
    int fd1 = open("hello.txt", O_RDONLY, 0666);
    read(fd, buffer, strlen(str));
    printf("%s\n", buffer);
    close(fd1);
    return 0;
}
