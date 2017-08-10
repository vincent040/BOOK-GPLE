#ifndef _HEAD4SEM_H_
#define _HEAD4SEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHMSZ 128

#define PROJ_PATH "."
#define ID4SHM 1
#define ID4SEM 2

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

static void sem_p(int semid, int semnum)
{
	struct sembuf op[1];
	op[0].sem_num = semnum;
	op[0].sem_op  = -1;
	op[0].sem_flg = 0;

	semop(semid, op, 1);
}

static void sem_v(int semid, int semnum)
{
	struct sembuf op[1];
	op[0].sem_num = semnum;
	op[0].sem_op  = 1;
	op[0].sem_flg = 0;

	semop(semid, op, 1);
}

static void seminit(int semid, int semnum, int value)
{
	union semun a;
	a.val = value;
	semctl(semid, semnum, SETVAL, a);
}

#endif
