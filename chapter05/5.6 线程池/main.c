//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.6/main.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 一个使用了线程池的示例
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "thread_pool.h"

void *mytask(void *arg)
{
	int n = (int)arg;

	printf("[%u][%s] ==> job will be done in %d sec...\n",
		(unsigned)pthread_self(), __FUNCTION__, n);

	sleep(n);

	printf("[%u][%s] ==> job done!\n",
		(unsigned)pthread_self(), __FUNCTION__);

	return NULL;
}

void *count_time(void *arg)
{
	int i = 0;
	while(1)
	{
		sleep(1);
		printf("sec: %d\n", ++i);
	}
}

int main(void)
{
	pthread_t a;
	pthread_create(&a, NULL, count_time, NULL);

	// 1, initialize the pool
	thread_pool *pool = malloc(sizeof(thread_pool));
	init_pool(pool, 2);

	// 2, throw tasks
	printf("throwing 3 tasks...\n");
	add_task(pool, mytask, (void *)(rand()%10));
	add_task(pool, mytask, (void *)(rand()%10));
	add_task(pool, mytask, (void *)(rand()%10));

	// 3, check active threads number
	printf("current thread number: %d\n",
			remove_thread(pool, 0));
	sleep(9);

	// 4, throw tasks
	printf("throwing another 2 tasks...\n");
	add_task(pool, mytask, (void *)(rand()%10));
	add_task(pool, mytask, (void *)(rand()%10));

	// 5, add threads
	add_thread(pool, 2);

	sleep(5);

	// 6, remove threads
	printf("remove 3 threads from the pool, "
	       "current thread number: %d\n",
			remove_thread(pool, 3));

	// 7, destroy the pool
	destroy_pool(pool);
	return 0;
}
