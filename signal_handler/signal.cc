#include <iostream>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
    std::cout << "get a signal:" << sig << std::endl;
}

int main()
{
    // 发送从1到31的31个普通信号
    for (int i = 1; i <= 31; i++)
    {
        signal(i, handler);
    }
    while (1)
    {
        sleep(1);
    }
    return 0;
}