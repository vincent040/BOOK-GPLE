//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.4/create_exit_join.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了线程创建、退出以及接合等基本操作接口函数
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <pthread.h>

void *routine(void *arg)
{
	char *s = (char *)arg;
	printf("argument: %s", s);

	sleep(1);
	pthread_exit("Bye-Bye!\n");
}

int main(int argc, char **argv)
{
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)"testing string\n");

	void *p;
	pthread_join(tid, &p);
	
	printf("exit value: %s", (char *)p);
	return 0;
}
