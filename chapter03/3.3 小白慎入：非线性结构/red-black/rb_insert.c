//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/rb_insert.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 红黑树节点添加算法实现源码
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef RB
#define RB
#endif

#include "drawtree.h"
#include "head4tree.h"
#include "head4rb.h"

void insert_fixup(linktree *proot, linktree new)
{
	if(new->parent == NULL)
	{
		new->color = BLACK;
		*proot = new;
		return;
	}

	if(new->parent->color == BLACK) // 1: 黑父
		return;
	else
		insert_case1(proot, new);
}

void insert_case1(linktree *proot, linktree new)
{
	if(uncle(new) != NULL && uncle(new)->color == RED) // 2: 红父 + 红叔
	{
		new->parent->color = BLACK;
		uncle(new)->color = BLACK;
		grandparent(new)->color = RED;

		insert_fixup(proot, grandparent(new));
	}
	else
		insert_case2(proot, new);
}


void insert_case2(linktree *proot, linktree new) // 3: 红父 + 黑叔
{

	if(new == new->parent->rchild &&
			new->parent == grandparent(new)->lchild)
	{
		rb_rotate_left(proot, new);
		new = new->lchild;
	}

	else if(new == new->parent->lchild &&
			new->parent == grandparent(new)->rchild)
	{
		rb_rotate_right(proot, new);
		new = new->rchild;
	}

	insert_case3(proot, new);
}


void insert_case3(linktree *proot, linktree new) // 3: 红父 + 黑叔
{
	new->parent->color = BLACK;
	grandparent(new)->color = RED;

	if(new == new->parent->lchild &&
			new->parent == grandparent(new)->lchild)
	{
		rb_rotate_right(proot, new->parent);
	}
	else
		rb_rotate_left(proot, new->parent);
}

linktree bst_insert(linktree root, linktree new)
{
	if(root == NULL)
		return new;

	new->parent = root;
	if(new->data < root->data)
	{
		root->lchild = bst_insert(root->lchild, new);
	}

	else if(new->data > root->data)
	{
		root->rchild = bst_insert(root->rchild, new);
	}
	else
	{
		printf("%d exist.\n", new->data);
	}

	return root;
}

void rb_insert(linktree *proot, linktree new)
{
	*proot = bst_insert(*proot, new);
	insert_fixup(proot, new);
}
