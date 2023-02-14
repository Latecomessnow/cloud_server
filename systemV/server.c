#include"comm.h"

int main()
{
    key_t key = ftok(PATHNAME, PROJ_ID);
    if (key < 0)
    {
        perror("ftok");
        return 1;
    }
   int shm = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0666);
   if (shm <0)
   {
       perror("shmget");
       return 2;
   }

   printf("key:%x\n", key);
   printf("shm:%d\n", shm);

   // 关联共享内存
   char* mem =(char*) shmat(shm, NULL, 0);

   while (1)
   {
        printf("client sent:%s\n", mem);
        sleep(1);
   }

   // 去关联
   shmdt(mem);
   // 释放共享内存 
   shmctl(shm, IPC_RMID, NULL);

   return 0;
}
