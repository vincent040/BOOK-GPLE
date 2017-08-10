////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/queue.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 链队列
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include "head4queue.h"

linkqueue init_queue(void)
{
	linkqueue q = (linkqueue)malloc(sizeof(queuenode));
	q->front = q->rear =
		(struct _queue_node *)malloc(sizeof(struct _queue_node));
	q->rear->next = NULL;

	return q;
}

bool is_empty_q(linkqueue q)
{
	return (q->front == q->rear);
}

bool out_queue(linkqueue q, qn_datatype *pdata)
{
	if(is_empty_q(q))
		return false;

	struct _queue_node *p = q->front;

	q->front = q->front->next;
	free(p);
	*pdata = q->front->data;

	return true;
}

bool en_queue(linkqueue q, qn_datatype data)
{
	struct _queue_node *pnew;
	pnew = (struct _queue_node *)malloc(sizeof(struct _queue_node));
	if(pnew == NULL)
		return false;

	pnew->data = data;
	pnew->next = NULL;

	q->rear->next = pnew;
	q->rear = pnew;

	return true;
}

#ifdef QUEUE_SIZE
int queue_size(linkqueue *q)
{
	return q->size;
}
#endif
