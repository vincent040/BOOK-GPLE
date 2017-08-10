//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/head4rb.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 红黑树算法头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef _HEAD4RB_H_
#define _HEAD4RB_H_

#ifndef RB
#define RB
#endif
#include "head4tree.h"

inline linktree grandparent(linktree n)
{
	if(n == NULL || n->parent == NULL)
		return NULL;

	return n->parent->parent;
}

static linktree uncle(linktree n)
{
	linktree gp = grandparent(n);

	if(gp == NULL)
		return NULL;

	return n->parent == gp->lchild ?
		gp->rchild : gp->lchild;
}

static linktree sibling(linktree n)
{
	if(n == NULL || n->parent == NULL)
	{
		return NULL;
	}

	if(n == n->parent->lchild)
		return n->parent->rchild;
	else
		return n->parent->lchild;
}

static linktree left_nephew(linktree n)
{
	return sibling(n)==NULL ? NULL : sibling(n)->lchild;
}

static linktree right_nephew(linktree n)
{
	return sibling(n)==NULL ? NULL : sibling(n)->rchild;
}

static int Color(linktree n)
{
	return n==NULL ? BLACK : n->color;
}


void rotate_left(linktree *proot, linktree n);
void rotate_right(linktree *proot, linktree n);

linktree rb_find(linktree root, tn_datatype data);
linktree bst_insert(linktree root, linktree new);

void insert_case1(linktree *proot, linktree new);
void insert_case2(linktree *proot, linktree new);
void insert_case3(linktree *proot, linktree new);
void rb_insert(linktree *proot, linktree new);
void insert_fixup(linktree *proot, linktree new);

void rb_delete(linktree *proot, tn_datatype data);
void real_delete(linktree *proot, linktree old);
void delete_fixup(linktree *proot, linktree new, linktree parent);

#endif
