//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/shm/Rose.c
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

int main(int argc, char **argv)
{
	key_t key = ftok(PROJ_PATH, PROJ_ID);
	int shmid = shmget(key, SHMSIZE, 0666);

	char *p = shmat(shmid, NULL, 0);
	printf("from SHM: %s", p+sizeof(pid_t));

	kill(*((pid_t *)p), SIGINT);
	shmdt(p);
	
	return 0;
}
