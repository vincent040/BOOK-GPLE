//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/head4queue.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 本文件为队列核心头文件。
//               任何使用本队列算法的程序，在包含本头文件之前都需要
//               将如下宏定义成队列节点需要表达的数据类型：
//
//                     QUEUE_NODE_DATATYPE
//
//               否则队列的节点数据类型一律默认为 int
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef _HEAD4QUEUE_H__
#define _HEAD4QUEUE_H__

#include "commonheader.h"

#ifndef QUEUE_NODE_DATATYPE 
#define QUEUE_NODE_DATATYPE int 
#endif

typedef QUEUE_NODE_DATATYPE qn_datatype;

struct _queue_node
{
	qn_datatype data;
	struct _queue_node *next;

};

typedef struct _queuenode
{
	struct _queue_node *front;
	struct _queue_node *rear;
#ifdef QUEUE_SIZE
	int size;
#endif
}queuenode, *linkqueue;

bool is_empty_q(linkqueue);
bool out_queue(linkqueue, qn_datatype *);
bool en_queue(linkqueue, qn_datatype);
linkqueue init_queue(void);

#ifdef QUEUE_SIZE
int queue_size(linkqueue *);
#endif

#endif

