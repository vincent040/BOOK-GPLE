//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/shm/Jack.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用共享内存，来实现两个进程间的数据共享
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4shm.h"
#include <signal.h>

int shmid;

void rmid(int sig)
{
	shmctl(shmid, IPC_RMID, NULL);
}

int main(int argc, char **argv)
{
	signal(SIGINT, rmid);

	key_t key = ftok(PROJ_PATH, PROJ_ID);
	shmid = shmget(key, SHMSIZE, IPC_CREAT|0666);

	char *p = shmat(shmid, NULL, 0);
	bzero(p, SHMSIZE);

	pid_t pid = getpid();
	memcpy(p, &pid, sizeof(pid_t));

	fgets(p+sizeof(pid_t), SHMSIZE, stdin);
	pause();

	return 0;
}
