#include <iostream>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int count = 1;

void* printNumbers(void* id) {
    int threadId = *((int*)id);
    while (count <= 100) {
        pthread_mutex_lock(&mutex);
        while (count % 3 != threadId) {
            pthread_cond_wait(&cond, &mutex);
        }
        
        if (count <= 100) {
            std::cout << "Thread " << threadId << ": " << count << std::endl;
            ++count;
        }
        
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int threadIds[3] = {0, 1, 2};
    
    for (int i = 0; i < 3; ++i) {
        pthread_create(&threads[i], NULL, printNumbers, &threadIds[i]);
    }
    
    for (int i = 0; i < 3; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    return 0;
}

