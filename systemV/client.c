#include"comm.h"

int main()
{
    key_t key = ftok(PATHNAME, PROJ_ID);
    if (key < 0)
    {
        perror("ftok");
        return 1;
    }

    // 重新获取shm，重新shmget并关联起来
    // 获取server进程创建的的共享内存用户层id
    int shm = shmget(key, SIZE, IPC_CREAT);
    if (shm < 0)
    {
        perror("shmget");
        return 2;
    }

    printf("key:%x\n", key);
    printf("shm:%d\n", shm);
    
    char* mem =(char*) shmat(shm, NULL, 0);

    int i = 0;
    while (1)
    {
        mem[i++] = 'A' + i;
        mem[i] = '\0';
        sleep(1);
    }

    shmdt(mem);
    return 0;
}
