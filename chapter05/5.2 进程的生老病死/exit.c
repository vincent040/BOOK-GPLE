//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.2/exit.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示exit()/_exit()等函数的使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void routine1(void)
{
	printf("routine1 is called.\n");
}

void routine2(void)
{
	printf("routine2 is called.\n");
}

int main(int argc, char **argv)
{
	atexit(routine1);
	atexit(routine2);

	fprintf(stdout, "abcdef");

#ifdef _EXIT
	_exit(0);
#else
	exit(0);
#endif
}
