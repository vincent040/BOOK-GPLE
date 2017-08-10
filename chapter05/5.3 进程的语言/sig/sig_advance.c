//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/sig/sig_advance.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了Linux中信号的高级使用技巧
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int sig, siginfo_t *sinfo, void *p)
{
	printf("catch %d.\n", sig);

	if(sinfo->si_code == SI_QUEUE)
	{
		printf("%d\n", sinfo->si_int);
	}
}

int main(int argc, char **argv)
{
	pid_t x = fork();

	if(x > 0)
	{
		struct sigaction act;
		bzero(&act, sizeof(act));
		act.sa_sigaction = sighandler;
		act.sa_flags |= SA_SIGINFO;
		sigaction(SIGINT, &act, NULL);

		pause();
	}

	if(x == 0)
	{
		sleep(1);

		union sigval data;
		data.sival_int = 100;
		sigqueue(getppid(), SIGINT, data);
	}

	return 0;
}
