#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "ringQueue.hpp"

void* Producer(void* arg)
{
    RingQueue<int>* rq = (RingQueue<int>*)arg;
    while (true)
    {
        sleep(1);
        int data = rand() % 100 + 1;
        rq->Push(data);
        std::cout << "Producer produce a data: " << data << std::endl;
    }
}

void* Consumer(void* arg)
{
    RingQueue<int>* rq = (RingQueue<int>*)arg;
    while (true)
    {
        sleep(1);
        int data = 0;
        rq->Pop(data);
        std::cout << "Consumer consume a data: " << data << std::endl;
    }
}

int main()
{
    srand((unsigned int)time(nullptr));
    RingQueue<int>* rq = new RingQueue<int>;
    pthread_t producer, consumer;
    pthread_create(&producer, nullptr, Producer, (void*)rq);
    pthread_create(&consumer, nullptr, Consumer, (void*)rq);

    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);
    delete rq;
    return 0;
}