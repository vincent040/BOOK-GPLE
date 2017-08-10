//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.2/callback.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了回调函数的基本用法
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <signal.h>


void sighandler(int sig)
{
	printf("sig : %d\n", sig);
}

int main(void)
{

	signal(SIGINT, sighandler);
	

	pid_t myPID = getpid();
	kill(myPID, SIGINT);

	return 0;
}
