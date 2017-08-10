//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.3/function_pointer.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示函数指针的定义和使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

int main(void)
{
	double   f (int a, char c);
	double (*p)(int a, char c);

	p = &f;

	double ans1 =   f (100, 'x');
	double ans2 = (*p)(100, 'x');

	printf("%lf\n", ans1);
	printf("%lf\n", ans2);

	return 0;
}

double f(int a, char c)
{
	double answer;

	double _a = (double)a;
	double _b = (double)c;

	answer = _a / _b;

	return answer;
}
