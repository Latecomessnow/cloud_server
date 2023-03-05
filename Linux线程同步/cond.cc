#include <iostream>
#include <pthread.h>

pthread_mutex_t mutex;
// 条件变量的使用需要配合互斥锁
pthread_cond_t cond;

void *Routine(void *arg)
{
    std::cout << (char *)arg << "启动" << std::endl;
    pthread_mutex_lock(&mutex);
    while (true)
    {
        // 线程阻塞在这里, 等待条件变量的成立
        // 所以在调用pthread_cond_wait函数时，还需要将对应的互斥锁传入，
        // 此时当线程因为某些条件不满足需要在该条件变量下进行等待时，就会自动释放该互斥锁。
        pthread_cond_wait(&cond, &mutex);
        std::cout << (char *)arg << "被唤醒" << std::endl;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(nullptr);
}

int main()
{
    // 创建3个线程，这三个线程都在cond这个条件变量下等待，当键盘有输入时唤醒一个等待线程
    pthread_t t1, t2, t3;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&t1, nullptr, Routine, (void *)"thread-1");
    pthread_create(&t2, nullptr, Routine, (void *)"thread-2");
    pthread_create(&t3, nullptr, Routine, (void *)"thread-3");

    while (true)
    {
        // 键盘有输入时唤醒线程
        getchar();
        // 此时我们可以看到线程是有序地(1->2->3)被唤醒的，
        // 即我们所期望的线程同步(线程按照一定顺序执行)
        // 唤醒条件变量的资源等待队列中的首个线程
        pthread_cond_signal(&cond); // 线程被唤醒时会自动获得对应的互斥锁

        // 唤醒全部线程
        // pthread_cond_broadcast(&cond);
    }

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}