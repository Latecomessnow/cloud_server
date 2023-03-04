#include <iostream>
#include <pthread.h>

pthread_mutex_t mutex;

// 单执行流也是可能会产生死锁的
void* Routine(void* arg)
{
    pthread_mutex_lock(&mutex);
    // 已经申请锁了，还没有释放就再申请锁了，会造成死锁问题
    pthread_mutex_lock(&mutex);
    // ps axj | head -1&&ps axj | grep deadlock | grep -v grep
    // 使用ps命令查看线程状态可以看到该状态为 Sl+ 该状态表示一种死锁的状态
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid, NULL, Routine, NULL);

    pthread_join(tid, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}