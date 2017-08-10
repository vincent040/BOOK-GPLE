//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.2/recursive_func.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了递归函数的基本思路
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

void f(int n);

int main(void)
{
	f(10);

	return 0;
}

void f(int n)
{
	if(n > 1)
	{
		f(n-1);
	}

	printf("%d\n", n);
}
