//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.5/enum.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了枚举的特性和使用细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>


enum spectrum {red, green, blue};

int main(void)
{
	enum spectrum color;
	color = green;	

	switch(color)
	{
	case red:
		printf("red\n");
		break;
	case green:
		printf("green\n");
		break;
	case blue:
		printf("blue\n");
		break;
	default:
		printf("unknown color\n");
	}

	return 0;
}
