#include <semaphore.h>

// 信号量的本质其实就是一把计数器
class Sem
{
public:
    // 初始信号量的资源数
    Sem(int num = 1)
    {
        // 0表示线程间共享，非0表示进程共享
        sem_init(&_sem, 0, num);
    }

    ~Sem()
    {
        sem_destroy(&_sem);
    }

    // P操作申请信号量，申请成功返回0，计数器-1
    void P()
    {
        sem_wait(&_sem);
    }

    // V操作释放信号量，释放成功返回0，计数器+1
    void V()
    {
        sem_post(&_sem);
    }
private:
    sem_t _sem;
};