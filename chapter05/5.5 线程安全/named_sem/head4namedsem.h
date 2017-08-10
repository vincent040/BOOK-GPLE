#ifndef _HEAD4NAMESEM_H_
#define _HEAD4NAMESEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#define PROJ_PATH "." // 用以产生共享内存的路径和整数
#define PROJ_ID 100

#define SHMSZ 1024 // 共享内存的大小
#define SEMNAME "sem4test" // 有名信号量的名字

#endif
