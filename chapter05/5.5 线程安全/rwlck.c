//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.5/rwlck.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了读写锁的使用方法，以及效果
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static pthread_rwlock_t rwlock;
static int global = 0;

void *routine1(void *arg)
{
	pthread_rwlock_wrlock(&rwlock);
	global += 1;
	printf("I am %s, now global=%d\n", (char *)arg, global);
	pthread_rwlock_unlock(&rwlock);

	pthread_exit(NULL);
}

void *routine2(void *arg)
{
	pthread_rwlock_wrlock(&rwlock);
	global  = 100;
	printf("I am %s, now global=%d\n", (char *)arg, global);
	pthread_rwlock_unlock(&rwlock);

	pthread_exit(NULL);
}

void *routine3(void *arg)
{
	pthread_rwlock_rdlock(&rwlock);
	printf("I am %s, now global=%d\n", (char *)arg, global);
	pthread_rwlock_unlock(&rwlock);

	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{

	pthread_rwlock_init(&rwlock,NULL);

	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, routine1, "thread 1");
	pthread_create(&t2, NULL, routine2, "thread 2");
	pthread_create(&t3, NULL, routine3, "thread 3");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_rwlock_destroy(&rwlock);
	
	return 0;
}
