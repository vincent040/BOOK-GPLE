//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.2/child_elf.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 配合程序GPLE/ch05/5.2/wait.c使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("[%d]: yep, I am the child\n", (int)getpid());

#ifdef ABORT
	abort();
#else
	exit(7);
#endif
}
