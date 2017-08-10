//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.2/linked_stack.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 用链式存储方式实现栈逻辑：链式栈
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
	int data;
	struct node *next;
};

struct linked_stack
{
	struct node *top;
	int size;
};

struct node *new_node(int data)
{
	struct node *new;
	new = malloc(sizeof(struct node));

	if(new != NULL)
	{
		new->data = data;
		new->next = NULL;
	}

	return new;
}

struct linked_stack *init_stack(void)
{
	struct linked_stack *s;
	s = malloc(sizeof(struct linked_stack));

	if(s != NULL)
	{
		s->top = NULL;
		s->size = 0;
	}

	return s;
}

bool stack_empty(struct linked_stack *s)
{
	return s->size == 0;
}

bool push(struct linked_stack *s, struct node *new)
{
	if(s == NULL || new == NULL)
		return false;

	new->next = s->top;
	s->top = new;
	s->size++;

	return true;
}

bool pop(struct linked_stack *s, int *p)
{
	if(s == NULL || p == NULL || stack_empty(s))
		return false;

	struct node *tmp = s->top;
	*p = tmp->data;
	
	s->top = s->top->next;
	s->size--;
	free(tmp);

	return true;
}

int main(void)
{
	struct linked_stack *s;
	s = init_stack();

	int n;
	scanf("%d", &n);
	
	while(n > 0)
	{
		struct node *new = new_node(n%8);
		push(s, new);
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
