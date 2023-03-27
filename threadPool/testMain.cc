#include "Task.hpp"
#include "threadPool.hpp"
#include <unistd.h>

int main()
{
    srand((unsigned int)time(nullptr));
    ThreadPool<Task> *tp = new ThreadPool<Task>;
    tp->ThreadPoolInit();
    const char *op = "+-*/%";
    while (true)
    {
        sleep(1);
        int x = rand() % 100 + 1;
        int y = rand() % 100 + 1;
        Task t(x, y, op[rand() % 5]);
        tp->Push(t);
    }
    return 0;
}