////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/traval.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 二叉树遍历：前序遍历、中序遍历、后序遍历和按层遍历
//               所有的遍历算法，都采用如下接口的函数来访问树节点：
//
//                        void handler(linktree root);
//
//               因此，使用本文件遍历算法时，应用程序需提供上述接口
//               函数的定义。
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include "commonheader.h"
#include "head4tree.h"

#define QUEUE_NODE_DATATYPE linktree
#include "head4queue.h"

void pre_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;
	
	handler(root);
	pre_travel(root->lchild, handler);
	pre_travel(root->rchild, handler);
}

void mid_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;
	
	mid_travel(root->lchild, handler);
	handler(root);
	mid_travel(root->rchild, handler);
}

void post_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;

	post_travel(root->lchild, handler);
	post_travel(root->rchild, handler);
	handler(root);
}

void level_travel(linktree root, void (*handler)(linktree))
{
	if(root == NULL)
		return;

	linkqueue q;
	q = init_queue();

	en_queue(q, root);

	linktree tmp;
	while(1)
	{
		if(!out_queue(q, &tmp))
			break;

		handler(tmp);

		if(tmp->lchild != NULL)
			en_queue(q, tmp->lchild);
		if(tmp->rchild != NULL)
			en_queue(q, tmp->rchild);
	}
}
