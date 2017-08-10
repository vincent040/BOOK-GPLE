//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/sig/target.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 本程序阻塞除SIGKILL和SIGSTOP之外的所有信号10秒钟
//               在此期间给本程序发信号，观察效果。10秒钟之后解除
//               阻塞，再观察效果。
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int sig)
{
	fprintf(stderr, "catch %d.\n", sig);
}

int main(int argc, char **argv)
{
	sigset_t sigs;
	sigemptyset(&sigs);

	int i;
	for(i=SIGHUP; i<=SIGRTMAX; i++)
	{
		if(i == SIGKILL || i == SIGSTOP)
			continue;

		signal(i, sighandler);
		sigaddset(&sigs, i);
	}

	printf("[%d]: blocked signals for a while...\n", getpid());
	sigprocmask(SIG_BLOCK, &sigs, NULL);
	sleep(10);

	printf("[%d]: unblocked signals.\n", getpid());
	sigprocmask(SIG_UNBLOCK, &sigs, NULL);
	
	return 0;
}
