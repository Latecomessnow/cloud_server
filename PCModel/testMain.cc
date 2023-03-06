#include "BlockingQueue.hpp"

// 由于我们实现的是单生产者、单消费者的生产者消费者模型，
// 因此我们不需要维护生产者和生产者之间的关系，也不需要维护消费者和消费者之间的关系，
// 我们只需要维护生产者和消费者之间的同步与互斥关系即可。

void* Producer(void* arg)
{
    BlockQueue<int>* bq = (BlockQueue<int>*)arg;
    // 生产者不断进行生产
    while (1)
    {
        sleep(1);
        int data = rand() % 100 + 1;
        bq->Push(data);
        std::cout << "Producer: " << data << std::endl;
    }
}

void* Consumer(void* arg)
{
    BlockQueue<int>* bq = (BlockQueue<int>*)arg;
    while (1)
    {
        sleep(1);
        int data = 0;
        bq->Pop(&data);
        std::cout << "Consumer: " << data << std::endl;
    } 
}

int main()
{
    srand((unsigned int)time(nullptr));

    pthread_t producer, consumer;
    BlockQueue<int>* bq = new BlockQueue<int>;

    pthread_create(&producer, nullptr, Producer, (void*)bq);
    pthread_create(&consumer, nullptr, Consumer, (void*)bq);

    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);

    delete bq;
    return 0;
}