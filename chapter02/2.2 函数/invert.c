//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.2/invert.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 将一个数组里面的元素逆转
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>

void invert(int a[], int size);
void swap(int *px, int *py);
void show_value(int a[], int size);

int main(void)
{
	int a[5] = {100, 200, 300, 400, 500};
	invert(a, 5);

	show_value(a, 5);
}

void swap(int *px, int *py)
{
	int tmp;
	tmp = *px;
	*px = *py;
	*py = tmp;
}

void invert(int a[], int size)
{
	if(size <= 1)
		return;

	invert(a+1, size-2);
	swap(&a[0], &a[size-1]);
}

void show_value(int a[], int size)
{
	int i;
	for(i=0; i<size; i++)
	{
		printf("%d\t", a[i]);
	}
	printf("\n");
}
