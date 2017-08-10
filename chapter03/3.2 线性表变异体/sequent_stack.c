//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.2/sequent_stack.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 用顺序存储方式实现栈逻辑：顺序栈
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct sequent_stack
{
	int *stack;
	int total_size;
	int top;
};

struct sequent_stack *init_stack(int size)
{
	struct sequent_stack *s;
	s = malloc(sizeof(struct sequent_stack));

	if(s != NULL)
	{
		s->stack = calloc(size, sizeof(int));
		s->total_size = size;
		s->top = -1;
	}
	return s;
}

bool stack_empty(struct sequent_stack *s)
{
	return s->top == -1;
}

bool stack_full(struct sequent_stack *s)
{
	return s->top >= s->total_size-1;
}

bool push(struct sequent_stack *s, int data)
{
	if(stack_full(s))
		return false;

	s->top++;
	s->stack[s->top] = data;
	return true;
}

bool pop(struct sequent_stack *s, int *pdata)
{
	if(stack_empty(s))
		return false;

	*pdata = s->stack[s->top];
	s->top--;
	return true;
}

int main(void)
{
	struct sequent_stack *s;
	s = init_stack(10);

	int n;
	scanf("%d", &n);
	
	while(n > 0)
	{
		push(s, n%8);
		n /= 8;
	}
	
	int m;
	while(!stack_empty(s))
	{
		pop(s, &m);
		printf("%d", m);
	}
	printf("\n");

	return 0;
}
