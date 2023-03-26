#include <queue>
#include <pthread.h>

#define NUM 5;

template <class T>
class ThreadPool
{
public:
    ThreadPool(int num = NUM)
        : _thread_num(num);
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_cond, )
    }

    ~ThreadPool()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

    // Routine例程不断的去从任务队列中取任务去处理
    static void* Routine(void* arg)
    {
        // 分离线程使其不需要在pthread_join
        pthread_detach(pthread_self());
        ThreadPool* slef = (ThreadPool*)arg;

    }

    ThreadPoolInit()
    {
        pthread_t tid[_thread_num];
        for (int i = 0; i < _thread_num; i++)
        {
            // Routine例程是一个返回值、参数都是void*的函数
            // 而如果Routine是一个类内成员函数的话，其参数中会增加一个this指针的参数
            // 所以应将其设置为static静态成员函数
            pthread_create(&(tid + i), nullptr, Routine, this);
        }
    }


private:
    std::queue<T> _task_queue;
    size_t _thread_num;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
};