//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.2/sequent_queue.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 用顺序存储方式实现队列逻辑：循环队列
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int datatype;

typedef struct
{
	datatype *queue;

	unsigned int size;
	int front;
	int rear;
}sequent_queue;

sequent_queue *init_queue(unsigned int size)
{

	sequent_queue *q = malloc(sizeof(sequent_queue));
	if(q != NULL)
	{
		q->queue = calloc(size, sizeof(datatype));
		q->size = size;
		q->front = 0;
		q->rear  = 0;
	}
	return q;
}

bool queue_full(sequent_queue *q)
{
	return q->front == (q->rear+1) % q->size;
}

bool queue_empty(sequent_queue *q)
{
	return q->front == q->rear;
}

bool en_queue(sequent_queue *q, datatype data)
{
	if(queue_full(q))
		return false;

	q->rear = (q->rear+1) % q->size;
	q->queue[q->rear] = data;

	return true;
}

bool de_queue(sequent_queue *q, datatype *pdata)
{
	if(queue_empty(q))
		return false;

	q->front = (q->front+1) % q->size;
	*pdata = q->queue[q->front];
	return true;
}

void show(sequent_queue *q)
{
	if(queue_empty(q))
		return;

	int tmp = (q->front + 1) % q->size;
	int flag = 0;

	while(tmp != q->rear)
	{
		printf("%s%d", flag==0 ? "" : "-->", q->queue[tmp]);
		tmp = (tmp+1) % q->size;
		flag = 1;
	}
	printf("%s%d\n", flag==0 ? "" : "-->", q->queue[tmp]);
}

int main(void)
{
	sequent_queue *q;
	q = init_queue(10);

	int n, m, ret;
	while(1)
	{
		ret = scanf("%d", &n);
		if(ret == 1)
		{
			en_queue(q, n);
		}
		else if(ret == 0)
		{
			de_queue(q, &m);
			while(getchar() != '\n');
		}
		show(q);
	}

	return 0;
}
