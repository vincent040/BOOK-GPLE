//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.3/multiply_poionter.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示多级指针的定义和使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

int main(void)
{
	int v1 = 100;
	int *p1 = &v1;
	int **p4 = &p1;

	printf("%d\n", v1);
	printf("%d\n", *p1);
	printf("%d\n", **p4);

	return 0;
}
