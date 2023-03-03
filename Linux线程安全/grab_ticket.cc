#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

static int tickets = 1000;

// 例如，我们在上述的抢票系统中引入互斥量，每一个线程要进入临界区之前都必须先申请锁，
// 只有申请到锁的线程才可以进入临界区对临界资源进行访问，并且当线程出临界区的时候需要释放锁，
// 这样才能让其余要进入临界区的线程继续竞争锁。

// 互斥量
pthread_mutex_t mutex;

void *GrabTicket(void *arg)
{
    const char *name = (char *)arg;
    while (true)
    {
        // 访问临界资源 tickets 时进行加锁操作
        pthread_mutex_lock(&mutex);
        // 不加锁的情况下，if语句判断条件为真以后，代码可以并发的切换到其他线程。
        if (tickets > 0)
        {
            // 模拟抢到票后的操作
            usleep(100);
            printf("%s get a ticket... left: %d\n", name, --tickets);
            // 抢票成功后进行解锁操作，让其他线程取竞争这个锁资源
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
    // 走到这说明票已经被抢完了
    printf("%s quit!\n", name);
    pthread_exit(NULL);
}

// 主线程创建四个线程去进行抢票
// 代码执行完后可以看到票数会变为负数
// 这就是在多线程情况下，多个执行流不加保护的对临界资源进行访问的后果，会导致数据不一致的问题
int main()
{
    // 初始化互斥量
    pthread_mutex_init(&mutex, NULL); // 第二个参数为互斥量的属性

    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, nullptr, GrabTicket, (void *)"Thread-1");
    pthread_create(&t2, nullptr, GrabTicket, (void *)"Thread-2");
    pthread_create(&t3, nullptr, GrabTicket, (void *)"Thread-3");
    pthread_create(&t4, nullptr, GrabTicket, (void *)"Thread-4");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    // 销毁互斥量
    pthread_mutex_destroy(&mutex);
    return 0;
}

// #include <stdio.h>
// #include <unistd.h>
// #include <pthread.h>

// int tickets = 1000;
// pthread_mutex_t mutex;
// void* TicketGrabbing(void* arg)
// {
// 	const char* name = (char*)arg;
// 	while (1){
// 		pthread_mutex_lock(&mutex);
// 		if (tickets > 0){
// 			usleep(100);
// 			printf("[%s] get a ticket, left: %d\n", name, --tickets);
// 			pthread_mutex_unlock(&mutex);
// 		}
// 		else{
// 			pthread_mutex_unlock(&mutex);
// 			break;
// 		}
// 	}
// 	printf("%s quit!\n", name);
// 	pthread_exit((void*)0);
// }
// int main()
// {
// 	pthread_mutex_init(&mutex, NULL);
// 	pthread_t t1, t2, t3, t4;
// 	pthread_create(&t1, NULL, TicketGrabbing, (void*)"thread 1");
// 	pthread_create(&t2, NULL, TicketGrabbing, (void*)"thread 2");
// 	pthread_create(&t3, NULL, TicketGrabbing, (void*)"thread 3");
// 	pthread_create(&t4, NULL, TicketGrabbing, (void*)"thread 4");

// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	pthread_join(t3, NULL);
// 	pthread_join(t4, NULL);
// 	pthread_mutex_destroy(&mutex);
// 	return 0;
// }
