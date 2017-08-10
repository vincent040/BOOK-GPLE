//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.6/typedef.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示typedef的使用细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

int main(void)
{
	// 给int取个别名叫INTEGER，使用它们定义整型a是等价的
	typedef int INTEGER;
	INTEGER a;
	int	a;

	// 给char *取个别名叫String，使用它们定义字符指针b是等价的
	typedef char *String;	
	String b;
	char * b;

	// 给具有5个元素的数组类型int [5]取个别名叫ARRAY
	typedef int ARRAY[5];
	ARRAY c;	// 使用它们定义具有5个int型元素的数组c是等价的
	int c[5];

	// 给函数指针类型void (*)(int)取个别名叫FUNC_POINTER
	typedef void (*FUNC_PTR)(int);
	FUNC_PTR pf ;	// // 使用它们定义函数指针pf是等价的
	void (*pf)(int);

	return 0;
}