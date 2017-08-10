//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.4/heap.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示堆内存的特性和使用细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

int *heap_array(int *old_ptr, int n);
void show_value(int *ptr);

int main(void)
{
	int n, *p = (int *)malloc(1 * sizeof(int));
	p[0] = 1;

	while(1)
	{
		if(scanf("%d", &n) == 0)
			break;

		p = heap_array(p, n);
		show_value(p);
	}

	free(p);
	return 0;
}

int *heap_array(int *old_ptr, int n)
{
	int size= old_ptr[0] + 1;
	int *new_ptr;

	new_ptr = (int *)realloc(old_ptr,
				(size * sizeof(int)));

	new_ptr[0] = size;
	new_ptr[size-1] = n;

	return new_ptr;

}

void show_value(int *ptr)
{
	int i;
	printf("--->>> ");
	for(i=1; i<ptr[0]; i++)
	{
		printf("%d ", ptr[i]);
	}
	printf("<<<---\n");
}
