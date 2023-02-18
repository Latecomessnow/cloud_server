#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<pthread.h>
#include<fcntl.h>
#include<vector>
#define PATHNAME "/home/guhui/cloud_server/systemV"

// 整数标识符
#define PROJ_ID 0X666
// 共享内存的大小
#define SIZE 4096
