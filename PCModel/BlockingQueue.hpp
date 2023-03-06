#include <iostream>
#include <pthread.h>
#include <queue>
#include <unistd.h>

#define NUM 5

// 基于阻塞队列的生产消费模型
// 单生产---单消费

template <class T>
class BlockQueue
{
private:
    bool IsFull()
    {
        return _q.size() == _cap;
    }

    bool IsEmpty()
    {
        return _q.empty();
    }

public:
    BlockQueue(int cap = NUM)
        : _cap(cap)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_cond_init(&_full, nullptr);
        pthread_cond_init(&_empty, nullptr);
    }

    ~BlockQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_full);
        pthread_cond_destroy(&_empty);
    }

    // 向阻塞队列插入数据(生产者调用)
    void Push(const T &data)
    {
        // 访问临界资源前进行加锁
        pthread_mutex_lock(&_mutex);
        // 如果队列为满生产者则要进行阻塞等待
        while (IsFull())
        {
            pthread_cond_wait(&_full, &_mutex);
        }
        _q.push(data);
        // 出了临界资源要进行解锁
        pthread_mutex_unlock(&_mutex);
        // 此时队列中一定放有了数据，唤醒在空的条件变量下等待的消费者线程
        pthread_cond_signal(&_empty);
    }

    // 向阻塞队列中拿取数据(消费者调用)
    void Pop(T *out)
    {
        // 在进入临界区之前无论是否满足生产/消费条件都一律先加锁进行保护
        // 访问临界资源前需要进行加锁保护临界资源
        pthread_mutex_lock(&_mutex);
        // 如果队列为空消费者需要在空的条件变量下进行等待
        while (IsEmpty())
        {
            // 在空的条件变量下进行等待, 需要配合传入互斥锁
            pthread_cond_wait(&_empty, &_mutex);
        }
        *out = _q.front();
        _q.pop();
        pthread_mutex_unlock(&_mutex);
        // 此时队列一定不为满，唤醒在满的条件变量下等待的生产者线程
        pthread_cond_signal(&_full);
    }

private:
    std::queue<T> _q;
    int _cap;               // 阻塞队列最大数据个数
    pthread_mutex_t _mutex; // 互斥锁配合条件变量的使用，实现互斥同步
    pthread_cond_t _full;   // 队列为满时，生产者不能继续生产，需要在满的条件变量下等待
    pthread_cond_t _empty;  // 队列为空时，消费者不能继续消费，需要在空的条件变量下等待
};