//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.4/set_detachstate.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了如何创建十条分离的线程
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <pthread.h>

void *routine(void *arg)
{
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,
			PTHREAD_CREATE_DETACHED);

	pthread_t tid;
	int i=0;
	for(i=0; i<10; i++)
	{
		pthread_create(&tid, &attr, routine, NULL);
	}

	pause();
	return 0;
}
