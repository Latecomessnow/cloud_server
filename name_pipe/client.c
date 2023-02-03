#include"comm.h"

int main()
{
    // 服务端已创建命名管道，客户端只需打开即可
    // 因为客户端需要先从标准输出读取数据，再向命名管道中进行写入，所以打开文件时需要读写权限 
    int fd = open(FILE_NAME, O_WRONLY);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    char msg[128];
    while (1)
    {
        // 每次读取前清空message
        msg[0] = '\0';
        printf("Please send message:");
        fflush(stdout);
        // 从标准输入读取数据
        ssize_t s = read(0, msg, sizeof(msg) - 1);
        if (s > 0)
        {
            msg[s - 1] = '\0';
            // 将msg写入管道中
            write(fd, msg, strlen(msg));
        }
        else if (s == 0)
        {
            printf("file end\n");
            break;
        }
        else
        {
            perror("write");
            exit(1);
        }
    }
    // 关闭文件
    close(fd);
    return 0;
}
