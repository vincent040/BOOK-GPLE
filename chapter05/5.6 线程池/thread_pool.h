//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.6/thread_pool.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 本文件包含了线程池基本结构体定义，以及各个操作函
//               数的声明
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <errno.h>
#include <pthread.h>

#define MAX_WAITING_TASKS	1000
#define MAX_ACTIVE_THREADS	20

struct task
{
	void *(*task)(void *arg);
	void *arg;

	struct task *next;
};

typedef struct thread_pool
{
	pthread_mutex_t lock;
	pthread_cond_t  cond;
	struct task *task_list;

	pthread_t *tids;

	unsigned waiting_tasks;
	unsigned active_threads;

	bool shutdown;
}thread_pool;


bool
init_pool(thread_pool *pool,
          unsigned int threads_number);

bool
add_task(thread_pool *pool,
         void *(*task)(void *arg),
         void *arg);

int 
add_thread(thread_pool *pool,
           unsigned int additional_threads_number);

int 
remove_thread(thread_pool *pool,
              unsigned int removing_threads_number);

bool destroy_pool(thread_pool *pool);
void *routine(void *arg);

#endif
