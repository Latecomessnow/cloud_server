#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>

using std::cout;
using std::endl;

pthread_t main_thread;

// // 创建线程所执行的例程，参数和返回值都是void*,arg是传入的参数
// void *Routine(void *arg)
// {
//     // 可以观察到新线程和主线程的pid、ppid是一样的，这就说明了他们同属一个进程
//     cout << "I'm " << (char *)arg
//          << " pid: " << getpid() << " ppid: " << getppid() << endl;
//     sleep(1);
// }

// int main()
// {
//     pthread_t tid;
//     // tid是一个输出型参数，用来标识线程在用户层的ID
//     // 第二个参数*attr置为NULL表示使用默认属性
//     pthread_create(&tid, nullptr, Routine, (void *)"thread 1");
//     // 主线程不退出，死循环，主线程一旦退出，整个进程都会退出，其他线程也都会退出
//     while (1)
//     {
//         cout << "I'm main thread"
//              << " pid: " << getpid() << " ppid: " << getppid() << endl;
//         sleep(1);
//     }
//     return 0;
// }

////////////////////////////////////////////////////////////
// 创建多线程

// 创建线程所执行的例程，参数和返回值都是void*,arg是传入的参数
// 该函数可以被多个执行流执行，称之为可重入函数
void *Routine(void *arg)
{
    // while (1)
    // {
    //     // 可以观察到新线程和主线程的pid、ppid是一样的，这就说明了他们同属一个进程
    //     cout << "I'm " << (char *)arg
    //          << " pid: " << getpid() << " ppid: " << getppid() << " tid: " << pthread_self() << endl;
    //     sleep(1);
    // }

    // 1. 线程自己终止自己---pthread_exit()
    // 2. 取消其他线程---pthread_cancel(tid)
    int cnt = 5;
    while (cnt--)
    {
        // 可以观察到新线程和主线程的pid、ppid是一样的，这就说明了他们同属一个进程
        cout << "I'm " << (char *)arg
             << " pid: " << getpid() << " ppid: " << getppid() << " tid: " << pthread_self() << endl;
        sleep(2);
    }

    // 一个线程崩会导致所有线程崩溃
    // int a /= 0;

    // 取消主线程
    //pthread_cancel(main_thread);
    return NULL;
}

int main()
{
    main_thread = pthread_self();
    // 创建5个线程去执行不同的任务
    pthread_t tid[5];
    for (int i = 0; i < 5; i++)
    {
        // 给不同线程取不同的名字
        char *buffer = (char *)malloc(64);
        sprintf(buffer, "thread %d", i + 1);
        // 创建成功后返回0
        int pc = pthread_create(&tid[i], NULL, Routine, (void *)buffer);
        assert(pc == 0);
        // 创建时观察一下子线程,%lu表示无符号长整型        // 输出型参数，子线程tid已放入数组中
        printf("I'm %s pid: %d ppid: %d tid: %lu\n", buffer, getpid(), getppid(), tid[i]);
    }
    // while (1)
    // {
    //     cout << "I'm main thread"
    //          << " pid: " << getpid() << " ppid: " << getppid() << " tid: " << pthread_self() << endl;
    //     sleep(2);
    // }

    cout << "I'm main thread"
         << " pid: " << getpid() << " ppid: " << getppid() << " tid: " << pthread_self() << endl;
    sleep(1);

    // return 0;

    // 线程创建后也是需要被等待，然后释放资源的，要不然就会造成类似于僵尸进程的现象
    // 导致内存泄漏
    // 线程等待
    for (int i = 0; i < 5; i++)
    {
        // 第一个参数是待等待线程tid, 第二个参数是线程退出码
        // 线程退出码只有在线程正常退出时才有意义，因为如果线程异常
        // 整个进程都会退出，无法执行pthread_join了
        pthread_join(tid[i], NULL); // 不关心其退出码，设置为NULL
        printf("thread %d[%lu] quit!\n", i + 1, tid[i]);
    }
    return 0;
}