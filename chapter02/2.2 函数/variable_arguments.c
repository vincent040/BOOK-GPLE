//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.2/variable_arguments.c 
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了如何定义和使用变参函数
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <strings.h>

#define MAXLINE 80

double sumup(const char *format, ...);

int main(void)
{
	int i = 1;
	char c = 'a';
	double f = 0.618;


	printf("sumary: %f\n", sumup("#i#c#f", i, c, f));

	return 0;
}

double sumup(const char *format, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, format);

	int argnum = 0, i;
	char arg[MAXLINE];
	bzero(arg, MAXLINE);


	for(i = 0; format[i] != '\0'; i++)
	{
		if(format[i] == '#')
		{
			arg[argnum] = format[++i];
			argnum++;
		}
	}

	double sum = 0;
	int arg_int;
	double arg_double;

	for(i = 0; arg[i] != '\0'; i++)
	{
		switch(arg[i])
		{
		case 'i':
		case 'c':
			arg_int = va_arg(arg_ptr, int);
			sum += arg_int;
			break;
		case 'f':
			arg_double = va_arg(arg_ptr, double);
			sum += arg_double;
			break;
		default:
			printf("format error!\n");
			exit(1);
		}
	}
	//va_end(arg_ptr);

	return sum;
}
