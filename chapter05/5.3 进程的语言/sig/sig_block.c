//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/sig/sig_block.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了信号阻塞和解除阻塞的基本用法，注意编译时需
//               要定义宏TEST:
//
//                  gcc sig_block.c -o sig_block -DTEST
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

void sighandler(int sig)
{
	printf("[%d]: catch %d.\n", getpid(), sig);
}

int main(int argc, char **argv)
{
	pid_t x = fork();

	if(x > 0)
	{
		signal(SIGINT, sighandler);

		sigset_t sigmask;
		sigemptyset(&sigmask);
		sigaddset(&sigmask, SIGINT);

#ifdef TEST
		printf("[%d]: block SIGINT...\n", getpid());
		sigprocmask(SIG_BLOCK, &sigmask, NULL);
#endif
		sleep(5);
#ifdef TEST
		printf("[%d]: unblock SIGINT...\n", getpid());
		sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
#endif

		wait(NULL);
	}
	
	if(x == 0)
	{
		sleep(1);
		if(kill(getppid(), SIGINT) == 0)
		{
			printf("[%d]: SIGINT has been sended!\n",
					getpid());
		}
	}

	return 0;
}
