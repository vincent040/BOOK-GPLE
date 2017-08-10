//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/sig/sig_simple.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示信号处理的最基本函数接口的用法和特点
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int sig)
{
	printf("catched a signal: %d\n", sig);
}

int main(int argc, char **argv)
{
	signal(SIGHUP, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, sighandler);

	printf("[%d]: I am waitting for some signal...\n",
			getpid());
	pause();

	return 0;
}
