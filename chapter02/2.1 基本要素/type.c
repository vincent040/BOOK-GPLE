//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.1/type.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 通过一个不规范的类型转换，演示C语言中数据类型的本质
//               含义。
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

struct elephant
{
	char c;
	double f;
	int i;
	char s[5];
};

int main(void)
{
	int a;
	struct elephant x = {'a', 3.14, 100, "hey"};
	
	a = *( (int *)&x );
	printf("%d\n", a);

	return 0;
}
