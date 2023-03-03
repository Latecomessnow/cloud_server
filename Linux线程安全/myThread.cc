#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

using std::cout;
using std::endl;

// 全局变量的count其实就是临界资源
// 在多线程情况下，如果这多个执行流都自顾自的对临界资源进行操作，
// 那么此时就可能导致数据不一致的问题。解决该问题的方案就叫做互斥，互斥的作用就是，保证在任何时候有且只有一个执行流进入临界区对临界资源进行访问。


int count = 0;

void* Routine(void* arg)
{
    while (1)
    {
        count++;
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, Routine, nullptr);
    while (1)
    {
        cout << "count:" << count << endl;
        sleep(1);
    }
    pthread_join(tid, NULL);
    return 0;
}