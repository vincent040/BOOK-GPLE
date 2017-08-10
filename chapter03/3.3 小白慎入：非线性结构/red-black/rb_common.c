//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/rb_common.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 红黑树的各种算法
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

// ================= 1，叔伯兄弟 ================ //
/*
static linktree grandparent(linktree n)
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

// ================= 2，颜色获取 ================ //

static int Color(linktree n)
{
	return n==NULL ? BLACK : n->color;
}
*/

// ================= 3，旋转操作 ================ //

void rb_rotate_left(linktree *proot, linktree n)
{
	linktree gp = grandparent(n);
	linktree p = n->parent;


	p->rchild = n->lchild;
	if(n->lchild != NULL)
		n->lchild->parent = p;


	n->lchild = p;
	p->parent = n;


	if(*proot == p)
		*proot = n;


	n->parent = gp;
	if(gp != NULL)
	{
		if(p == gp->lchild)
			gp->lchild = n;
		else
			gp->rchild = n;
	}
}

void rb_rotate_right(linktree *proot, linktree n)
{
	linktree gp = grandparent(n);
	linktree p = n->parent;

	p->lchild = n->rchild;
	if(n->rchild != NULL)
		n->rchild->parent = p;

	n->rchild = p;
	p->parent = n;

	if(*proot == p)
		*proot = n;

	n->parent = gp;

	if(gp != NULL)
	{
		if(p == gp->lchild)
			gp->lchild = n;
		else
			gp->rchild = n;
	}
}

void rb_rotate_leftright(linktree *proot, linktree n)
{
	rb_rotate_left (proot, n);
	rb_rotate_right(proot, n);
}

void rb_rotate_rightleft(linktree *proot, linktree n)
{
	rb_rotate_right(proot, n);
	rb_rotate_left (proot, n);
}
