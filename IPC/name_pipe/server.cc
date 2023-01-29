#include"comm.hpp"

int main()
{
    // 1. 创建管道文件
    if (mkfifo(ipcPath.c_str(), MODE) < 0)
    {
        perror("mkfifo");
        exit(1);
    }

    // 2. 正常打开文件
    int fd = open(ipcPath.c_str(), O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(2);
    }

}