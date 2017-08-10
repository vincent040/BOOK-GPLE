//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.2/hanoi_stack.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用链栈方式解决汉诺塔问题
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
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

struct linked_stack *s1, *s2, *s3;

bool stack_empty(struct linked_stack *s)
{
	return s->size == 0;
}

struct node *new_node(int data)
{
	struct node *new = malloc(sizeof(struct node));
	if(new != NULL)
	{
		new->data = data;
		new->next = NULL;
	}
	return new;
}

bool push(struct linked_stack *s, struct node *new)
{
	if(new == NULL)
		return false;

	new->next = s->top;
	s->top = new;
	s->size++;

	return true;
}

bool pop(struct linked_stack *s, struct node **p)
{
	if(stack_empty(s))
		return false;

	*p = s->top;
	s->top = s->top->next;
	(*p)->next = NULL;
	s->size--;

	return true;
}

void show(struct linked_stack *s1,
	  struct linked_stack *s2,
	  struct linked_stack *s3)
{
	int maxlen, len;

	maxlen = s1->size > s2->size ? s1->size : s2->size;
	maxlen = maxlen > s3->size ? maxlen : s3->size;
	len = maxlen;

	struct node *tmp1 = s1->top;
	struct node *tmp2 = s2->top;
	struct node *tmp3 = s3->top;
	
	int i;
	for(i=0; i<maxlen; i++)
	{
		if(tmp1 != NULL && len <= s1->size)
		{
			printf("%d", tmp1->data);
			tmp1 = tmp1->next;
		}
		printf("\t");
		
		if(tmp2 != NULL && len <= s2->size)
		{
			printf("%d", tmp2->data);
			tmp2 = tmp2->next;
		}
		printf("\t");
		
		if(tmp3 != NULL && len <= s3->size)
		{
			printf("%d", tmp3->data);
			tmp3 = tmp3->next;
		}
		printf("\n");		

		len--;
	}
	printf("s1\ts2\ts3\n-----------------\n");
}

void hanoi(int n, struct linked_stack *ss1,
		  struct linked_stack *ss2,
		  struct linked_stack *ss3)
{
	if(n <= 0)
		return;

	struct node *tmp;

	hanoi(n-1, ss1, ss3, ss2);
	getchar();
	show(s1, s2, s3);
	pop(ss1, &tmp);
	push(ss2, tmp);
	hanoi(n-1, ss3, ss2, ss1);
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

int main(void)
{
	printf("how many hanois ? ");
	int hanois;
	scanf("%d", &hanois);

	s1 = init_stack();
	s2 = init_stack();
	s3 = init_stack();

	int i;
	for(i=0; i<hanois; i++)
	{
		struct node *new = new_node(hanois-i);
		push(s1, new);
	}

	hanoi(hanois, s1, s2, s3);
	show(s1, s2, s3);

	return 0;
}
