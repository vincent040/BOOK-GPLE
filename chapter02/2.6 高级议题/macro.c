//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.6/macro.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示C语言中宏的定义和使用细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

#define MAX(a, b) \
	({ \
		typeof(a) _a = a; \
		typeof(b) _b = b; \
		(void)(&_a == &_b); \
		((_a)>(_b) ? (_a) : (_b)); \
	})

void show(int a, float b, float m)
{
	printf("a=%d, b=%.2f, m=%.2f\n",
		a, b, m);
}

int main(void)
{
	int   a = 100;
	float b = 3.14;

	float m=0;

	show(a, b, m);
	m = MAX(a, b++);
	show(a, b, m);

	return 0;
}
