//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.3/multiply_array.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示多维数组和数组指针的定义和使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

int main(void)
{
	int c[0];
	int a[2][3] = {{100, 200, 300}, {77, 88, 99}};

	int (*p1)[2][3];
	int (*p2)[3];
	int (*p3);

	p1 = &a;
	p2 = &a[0];
	p3 = &a[0][0];

	printf("p1: %p\n", p1);
	printf("p2: %p\n", p2);
	printf("p3: %p\n", p3);

	printf("\n");

	printf("p1 + 1: %p\n", p1+1);
	printf("p2 + 1: %p\n", p2+1);
	printf("p3 + 1: %p\n", p3+1);

	return 0;
}
