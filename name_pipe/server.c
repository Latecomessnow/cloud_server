#include"comm.h"

int main()
{
    umask(0);
    // 服务端创建好命名管道以供客户端进行写入，然后服务端在进行读取
    if (mkfifo(FILE_NAME, 0666) < 0)
    {
        perror("mkfifo");
        exit(1);
    }

    // 进程间通信的本质就是让不同的进程看到同一份资源
    // 不同进程子需要打开同一个命名管道即可
    int fd = open(FILE_NAME, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(2);
    }
    char buffer[128];
    while (1)
    {
        // 每次读之前需要把buffer清空
        buffer[0] = '\0';
        // sizeof减1，因为系统级别的接口不关心C语言以\0结尾的规则
        ssize_t s = read(fd, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            // 手动设置\0，便于输出
            buffer[s] = '\0';
            // 输出客户端发送过来的信息
            printf("client send:%s\n", buffer);
        }

        // 正常结束读到0
        else if(s == 0)
        {
            printf("client quit!\n");
            break;
        }
        else
        {
            perror("read");
            exit(3);
        }

        // 通信完毕，关闭命名管道
    }

    close(fd);
    return 0;
}
