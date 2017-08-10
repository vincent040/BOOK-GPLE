//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.6/attribute4.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用attribute机制修改函数的属性
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

struct __attribute__((aligned(1024))) node
{
	int a;
	int b;
};

int main(void)
{
	printf("%d\n", sizeof(struct node));
	return 0;
}
