#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "sem.hpp"

int tickets = 1000;

// 初始值为1的信号量称之为二元信号量，类似于互斥锁
Sem sem(1);

void *GrabTicket(void *arg)
{
    const char *name = (char *)arg;
    while (true)
    {
        // 访问临界资源前进行P操作申请信号量
        sem.P();
        if (tickets > 0)
        {
            // 不能够少了模拟抢票后的处理动作
            usleep(1000);
            std::cout << name << " get a ticket. "
                      << "left: " << --tickets << std::endl;
            // 到这里已经访问完临界资源了，需要释放信号量
            sem.V();
        }
        else
        {
            // 退出临界资源前进行V操作释放信号量
            sem.V();
            break;
        }
    }
    std::cout << name << " quit!" << std::endl;
    pthread_exit(nullptr);
}

int main()
{
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, nullptr, GrabTicket, (void *)"thread-1");
    pthread_create(&t2, nullptr, GrabTicket, (void *)"thread-2");
    pthread_create(&t3, nullptr, GrabTicket, (void *)"thread-3");
    pthread_create(&t4, nullptr, GrabTicket, (void *)"thread-4");
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);
    return 0;
}