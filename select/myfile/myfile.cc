#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

using namespace std;

bool SetNonBlock(int fd)
{
    // 1. 获取零号文件描述符的读写标志位
    int fl = fcntl(fd, F_GETFL);
    if (fl < 0) return false;
    // 2. 将零号文件描述符设置成非阻塞
    fcntl(fd, F_SETFL, fl | O_NONBLOCK); // 注意需要传入读写标志位
    return true;
}

int main()
{
    // 将标准输入设置成非阻塞
    SetNonBlock(0); // 只需要设置一次后续都是非阻塞的了
    char buffer[1024];
    while (true)
    {
        errno = 0; // 每次读取时重置一下errno
        // 从标准输入中读取数据
        ssize_t s = read(0, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            buffer[s] = '\0';
            cout << "echo# " << buffer  << " errno: " << errno << " errnostring: " << strerror(errno) << endl;
        }
        else
        {
            // TODO 
            cout << "read \"error\"" << " errno: " << errno << " errnostring: " << strerror(errno) << endl;
            sleep(1);
        }
    }
    return 0;
}