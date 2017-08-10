//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/sem/Jack.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用信号量，来同步两个进程间的通信逻辑
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4sem.h"

int main(int argc, char **argv)
{
	key_t key1 = ftok(PROJ_PATH, ID4SHM);
	key_t key2 = ftok(PROJ_PATH, ID4SEM);


	int shmid = shmget(key1, SHMSZ, IPC_CREAT|0644);
	char *shmaddr = shmat(shmid, NULL, 0);


	int semid = semget(key2, 2, IPC_CREAT|IPC_EXCL|0644);
	if(semid == -1 && errno == EEXIST)
	{
		semid = semget(key2, 2, 0644);
	}
	else
	{
		seminit(semid, 0, 0);
		seminit(semid, 1, 1);
	}
	
	while(1)
	{
		sem_p(semid, 1);
		fgets(shmaddr, SHMSZ, stdin);
		sem_v(semid, 0);
	}

	return 0;
}
