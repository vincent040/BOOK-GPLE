//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.5/mutex.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了互斥锁的使用方法，以及效果
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t m;

void output(const char *string)
{
	const char *p = string;

	while(*p != '\0')
	{
		fprintf(stderr, "%c", *p);
		usleep(100);
		p++;
	}
}

void *routine(void *arg)
{
	pthread_mutex_lock(&m);
	output("message delivered by child.\n");
	pthread_mutex_unlock(&m);

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_mutex_init(&m, NULL);

	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);

	pthread_mutex_lock(&m);
	output("info output from parent.\n");
	pthread_mutex_unlock(&m);

	pthread_join(tid, NULL);
	pthread_mutex_destroy(&m);

	return 0;
}
