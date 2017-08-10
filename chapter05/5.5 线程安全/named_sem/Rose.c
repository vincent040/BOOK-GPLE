//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.5/named_sem/Rose.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用POSIX命名信号量，来同步两个进程间的通信
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4namedsem.h"

int main(int argc, char **argv)
{
	key_t key = ftok(PROJ_PATH, PROJ_ID); // 使用共享内存通信
	int id = shmget(key, SHMSZ, IPC_CREAT|0666);
	char *shmaddr = shmat(id, NULL, 0);

	sem_t *s;
	s = sem_open(SEMNAME, O_CREAT, 0777, 0);

	while(1)
	{
		sem_wait(s);

		if(!strncmp(shmaddr, "quit", 4)) // 若对方写入quit，则退出
			break;

		printf("from Jack: %s", shmaddr);
	}

	sem_close(s);
	return 0;
}
