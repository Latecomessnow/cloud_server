#pragma once

#include <semaphore.h>
#include <vector>

#define NUM 8

template <class T>
class RingQueue
{
public:
    RingQueue(int cap = NUM)
        : _cap(cap), _p_pos(0), _c_pos(0)
    {
        _q.reserve(_cap);
        sem_init(&_blank_sem, 0, _cap); // 空间资源一开始为满
        sem_init(&_data_sem, 0, 0);     // 数据资源一开始为空
    }

    ~RingQueue()
    {
        sem_destroy(&_blank_sem);
        sem_destroy(&_data_sem);
    }

    void Push(const T &data)
    {
        P(_blank_sem);
        _q[_p_pos] = data;
        // 生产成功释放数据资源信号量
        V(_data_sem);
        _p_pos++;
        _p_pos %= _cap;
    }

    void Pop(T &data)
    {
        P(_data_sem);
        data = _q[_c_pos];
        // 消费完成，释放该位置的空间资源信号量
        V(_blank_sem);
        _c_pos++;
        _c_pos %= _cap;
    }

private:
    void P(sem_t &s)
    {
        sem_wait(&s);
    }

    void V(sem_t &s)
    {
        sem_post(&s);
    }

private:
    std::vector<T> _q; // 使用vector模拟环形队列
    size_t _cap;       // 环形队列容量
    size_t _p_pos;     // 生产者位置
    size_t _c_pos;     // 消费者位置
    sem_t _blank_sem;  // 空间资源信号量
    sem_t _data_sem;   // 数据资源信号量
};