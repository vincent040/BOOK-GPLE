//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.2/linked_queue.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 用链式存储方式实现队列逻辑：链式队列
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int datatype;

struct node
{
	datatype data;
	struct node *next;
};

typedef struct
{
	struct node *front;
	struct node *rear;
	unsigned int size;
}linked_queue;

linked_queue *init_queue(void)
{
	linked_queue *q = malloc(sizeof(linked_queue));
	if(q != NULL)
	{
		q->front = q->rear = NULL;
		q->size = 0;
	}
	return q;
}

struct node *new_node(datatype data)
{
	struct node *new = malloc(sizeof(struct node));
	if(new != NULL)
	{
		new->data = data;
		new->next = NULL;
	}
	return new;
}

bool queue_empty(linked_queue *q)
{
	return q->size == 0;
}

bool en_queue(linked_queue *q, struct node *new)
{
	if(new == NULL)
		return false;

	if(queue_empty(q))
	{
		q->front = q->rear = new;
	}
	else
	{
		q->rear->next = new;
		q->rear = new;
	}

	q->size++;
	return true;
}

bool singular(linked_queue *q)
{
	return (!queue_empty(q)) && (q->front == q->rear);
}

bool de_queue(linked_queue *q, struct node **p)
{
	if(queue_empty(q))
		return false;

	struct node *tmp = q->front;

	if(singular(q))
	{
		q->front = q->rear = NULL;
	}
	else
	{
		q->front = q->front->next;
	}

	if(p != NULL)
	{
		tmp->next = NULL;
		*p = tmp;
	}
	else
	{
		free(tmp);
	}
	q->size--;

	return true;
}

void show(linked_queue *q)
{
	if(queue_empty(q))
		return;

	struct node *tmp = q->front;

	while(tmp != NULL)
	{
		printf("%d\t", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

int main(void)
{
	linked_queue *q;
	q = init_queue();
	
	int n, ret;
	while(1)
	{
		ret = scanf("%d", &n);

		if(ret == 1)
		{
			struct node *new = new_node(n);
			en_queue(q, new);
			show(q);
		}
		else if(ret == 0)
		{
			struct node *tmp;
			de_queue(q, &tmp);
			show(q);
			while(getchar() != '\n');
		}
	}

	return 0;
}
