//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.3/const_pointer.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示const型指针的定义和使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

int main(void)
{
	char data[] = "apple tree";
	printf("%d\n", get_len(data));	// 传递的其实是&data[0]

	return 0;	
}

int get_len(const char *data)
{
	int len = strlen(data);
	
	// 以下语句是错误的，指针data为const型，不可修改其目标内存
	//strcpy(data, "APPLE TREE");
	return len;
}
