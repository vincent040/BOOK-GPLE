//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.3/array_pointer.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示数组指针的定义和使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

int main(void)
{
	int   v5 [5] = {1, 2, 3, 4, 5};
	int (*p5)[5];

	p5 = &v5;

	int i;
	for(i=0; i<5; i++)
	{
		printf("  v5 [%d]: %d\t", i,   v5 [i]);
		printf("(*p5)[%d]: %d\n", i, (*p5)[i]);
	}

	return 0;
}
