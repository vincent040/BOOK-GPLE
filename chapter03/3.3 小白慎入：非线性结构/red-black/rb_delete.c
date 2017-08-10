//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/rb_delete.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 红黑树节点删除算法实现源码
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

linktree rb_find(linktree root, tn_datatype data)
{
	if(root == NULL)
		return NULL;

	if(data < root->data)
		return rb_find(root->lchild, data);
	else if(data > root->data)
		return rb_find(root->rchild, data);

	return root;
}

void delete_fixup(linktree *proot, linktree new, linktree parent)
{
	printf("%s\n", __FUNCTION__);

	linktree ln, rn; // left nephew & right nephew
	linktree s, gp;  // sibling & grandparent
	ln = rn = s = gp = NULL;

	if(new == NULL && parent == NULL) // 原来的old是树都唯一节点
	{
		*proot = NULL;
		return;
	}
	else if(new != NULL && parent == NULL) // 原来的old是根节点
	{
		*proot = new;
		return;
	}
	else if(parent != NULL)
	{
		s = parent->lchild ? parent->lchild : parent->rchild;
		gp = parent->parent;

		if(s != NULL)
		{
			ln = s->lchild;
			rn = s->rchild;
		}
	}

	//1，红兄
	if(Color(s) == RED)
	{
		if(new == parent->lchild)
		{
			rb_rotate_left(proot, s);
			parent->color = RED;
			s->color = BLACK;

			delete_fixup(proot, new, parent);
		}
		if(new == parent->rchild)
		{
			rb_rotate_right(proot, s);
			parent->color = RED;
			s->color = BLACK;

			delete_fixup(proot, new, parent);
		}
	}

	//2，黑兄
	if(Color(s) == BLACK)
	{

		//2.1，黑兄，二黑侄，红父
		if(Color(parent) == RED &&
		   Color(ln) == BLACK &&
		   Color(rn) == BLACK)
		{
			parent->color = BLACK;
			if(s != NULL)
				s->color = RED;
			return;
		}

		//2.2，黑兄，二黑侄，黑父
		if(Color(parent) == BLACK &&
		   Color(ln) == BLACK &&
		   Color(rn) == BLACK)
		{
			if(s != NULL)
			{
				s->color = RED;
			}

			delete_fixup(proot, parent, parent->parent);
		}

		//2.3，黑兄，同边红侄（同为左孩子）
		if(Color(ln) == RED && new == parent->lchild)
		{
			rb_rotate_right(proot, ln);
			rb_rotate_left(proot, ln);

			ln->color = parent->color;
			parent->color = BLACK;
		}
		// (同为右孩子)
		else if(Color(rn) == RED && new == parent->rchild)
		{
			rb_rotate_left(proot, rn);
			rb_rotate_right(proot, rn);

			rn->color = parent->color;
			parent->color = BLACK;
		}
		// 对边红侄(左右)
		else if(Color(ln) == RED && new == parent->rchild)
		{
			rb_rotate_right(proot, s);
			s->color = parent->color;

			parent->color = BLACK;
			ln->color = BLACK;
		}
		// 对边红侄(右左)
		else if(Color(rn) == RED && new == parent->lchild)
		{
			rb_rotate_left(proot, s);
			s->color = parent->color;

			parent->color = BLACK;
			rn->color = BLACK;
		}
	}
}

void real_delete(linktree *proot, linktree old)
{
	printf("%s\n", __FUNCTION__);

	// old不可能为NULL，new可能为NULL
	linktree new = old->lchild ? old->lchild : old->rchild;
	linktree parent = old->parent;

	if(old->parent != NULL)
	{
		if(old == old->parent->lchild)
			old->parent->lchild = new;
		else
			old->parent->rchild = new;

		old->parent = NULL;
	}
	if(new != NULL)
		new->parent = old->parent;


	if(Color(old) == BLACK && Color(new) == RED)
	{
		new->color = BLACK;
	}
	else if(Color(old) == BLACK && Color(new) == BLACK)
	{
		delete_fixup(proot, new, parent);
	}

	free(old);
}

void rb_delete(linktree *proot, tn_datatype data)
{
	linktree tmp = rb_find(*proot, data);
	if(tmp == NULL)
	{
		printf("%d is NOT exist.\n", data);
		return;
	}

	linktree n = tmp;
	if(tmp->lchild != NULL)
	{
		n = tmp->lchild;
		for(;n->rchild != NULL; n = n->rchild);
		tmp->data = n->data;
	}
	else if(tmp->rchild != NULL)
	{
		n = tmp->rchild;
		for(;n->lchild != NULL; n = n->lchild);
		tmp->data = n->data;
	}

	real_delete(proot, n); // n has ONE red-child at most
}
