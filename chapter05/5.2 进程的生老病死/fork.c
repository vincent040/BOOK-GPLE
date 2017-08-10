//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.2/fork.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示函数fork()的使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("[%d]: before fork() ... \n", getpid());

	pid_t x;
	x = fork();

	printf("[%d]: after fork() ...\n", getpid());
	return 0;
}
