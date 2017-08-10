//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.3/function_array.c
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

void show_value(int a[3]);

int main(void)
{
	int a[3] = {100, 200, 300};

	//show_value(  a  );
	  show_value(&a[0]);

	return 0;
}

//void show_value(int a[3])
  void show_value(int *p)
{
	int i;
	for(i=0; i<3; i++)
	{
		//printf("%d\n",  a[i]);
		//printf("%d\n", *(a+i));
		  printf("%d\n", *(p+i));
		  printf("%d\n",  p[i]);
	}
}
