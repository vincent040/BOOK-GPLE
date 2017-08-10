//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.2/exec.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了函数exec()的基本用法和特点
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t x;
	x = fork();

	if(x > 0)
	{
		printf("[%d]: I am the parent\n", (int)getpid());
		exit(0);
	}

	if(x == 0)
	{
		printf("[%d]: I am the child\n", (int)getpid());
		execl("./child_elf", "child_elf", NULL);

		printf("NEVER be printed\n");
	}

	return 0;
}
