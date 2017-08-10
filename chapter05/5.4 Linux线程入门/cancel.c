//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.4/cancel.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用函数pthread_cleanup_push()来规避由于线程取消
//               而导致死锁的问题
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t m;

void handler(void *arg)
{

	pthread_mutex_unlock(&m);

}

void *routine(void *arg)
{
	pthread_cleanup_push(handler, NULL);
	pthread_mutex_lock(&m);

	printf("[%u][%s]: abtained the mutex.\n",
			(unsigned)pthread_self(),
			__FUNCTION__);

	sleep(10);

	pthread_mutex_unlock(&m);
	pthread_cleanup_pop(0);

	pthread_exit(NULL);

}

int main(int argc, char **argv)
{

	pthread_mutex_init(&m, NULL);

	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);

	sleep(1);

	pthread_cancel(tid);
	pthread_mutex_lock(&m);

	printf("[%u][%s]: abtained the mutex.\n",
			(unsigned)pthread_self(),
			__FUNCTION__);

	pthread_mutex_unlock(&m);
	return 0;
}
