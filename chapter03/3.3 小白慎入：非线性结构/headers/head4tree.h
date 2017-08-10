//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/head4tree.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 本文件为二叉树核心头文件。
//               任何使用本二叉树结构算法的程序，在包含本头文件之前
//               都需要将如下宏定义成二叉树节点需要表达的数据类型：
//
//                     TREE_NODE_DATATYPE
//
//               否则二叉树的节点数据类型一律默认为 int
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef _HEAD4TREE_H_
#define _HEAD4TREE_H_

/*
 * Any application applying this linked-tree data structure should
 * define the macro "TREE_NODE_DATATYPE" before include this head
 * file, otherwise, the macro will be defined to 'int' as follow.
 *
*/

#ifndef TREE_NODE_DATATYPE
#define TREE_NODE_DATATYPE int
#endif

#include "commonheader.h"

#define MAX(a, b) ({ \
		typeof(a) _a = a; \
		typeof(b) _b = b; \
		(void)(&_a == &_b);\
		_a > _b? _a : _b; \
		})

typedef TREE_NODE_DATATYPE tn_datatype;

#ifdef RB
#define RED   0
#define BLACK 1
#endif

typedef struct _tree_node
{
	tn_datatype data;
	struct _tree_node *lchild;
	struct _tree_node *rchild;

#ifdef AVL
	int height;
#endif

#ifdef RB
	struct _tree_node *parent;
	int color;
#endif
}treenode, *linktree;

void pre_travel(linktree, void (*handler)(linktree));
void mid_travel(linktree, void (*handler)(linktree));
void post_travel(linktree, void (*handler)(linktree));
void level_travel(linktree, void (*handler)(linktree));

linktree bst_insert(linktree root, linktree new);
linktree bst_remove(linktree root, tn_datatype data);
linktree bst_find(linktree root, tn_datatype data);

#ifdef AVL
linktree avl_insert(linktree root, linktree new);
linktree avl_remove(linktree root, tn_datatype data);

linktree avl_rotate_left (linktree root);
linktree avl_rotate_right(linktree root);
linktree avl_rotate_leftright(linktree root);
linktree avl_rotate_rightleft(linktree root);

static int height(linktree root)
{
	return root==NULL ? 0 : root->height;
}
#endif

static linktree new_node(tn_datatype data)
{
	linktree new = malloc(sizeof(treenode));
	if(new != NULL)
	{
		new->data = data;
		new->lchild = NULL;
		new->rchild = NULL;

		#ifdef AVL
		new->height = 1;
		#endif

		#ifdef RB
		new->parent = NULL;
		new->color = RED;
		#endif
	}
	return new;
}

#endif
