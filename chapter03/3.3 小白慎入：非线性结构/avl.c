////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/avl.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: AVL算法实现代码
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include "head4tree.h"
#include "drawtree.h"

linktree avl_rotate_right(linktree root)
{
	linktree tmp = root->lchild;
	root->lchild = tmp->rchild;
	tmp->rchild = root;
	
	root->height = MAX(height(root->lchild), height(root->rchild)) + 1;
	tmp->height = MAX(height(tmp->lchild), root->height) + 1;

	return tmp;
}

linktree avl_rotate_left(linktree root)
{
	linktree tmp = root->rchild;
	root->rchild = tmp->lchild;
	tmp->lchild = root;
	
	root->height = MAX(height(root->lchild), height(root->rchild)) + 1;
	tmp->height = MAX(root->height, height(tmp->rchild)) + 1;

	return tmp;
}

linktree avl_rotate_leftright(linktree root)
{
	root->lchild = avl_rotate_left(root->lchild);
	return avl_rotate_right(root);
}

linktree avl_rotate_rightleft(linktree root)
{
	root->rchild = avl_rotate_right(root->rchild);
	return avl_rotate_left(root);
}

linktree avl_insert(linktree root, linktree new)
{
	if(root == NULL)
		return new;


	if(new->data < root->data)
		root->lchild = avl_insert(root->lchild, new);
	else if(new->data > root->data)
		root->rchild = avl_insert(root->rchild, new);
	else
	{
		printf("%d is already exist.\n", new->data);
	}


	if(height(root->lchild) - height(root->rchild) == 2)
	{
		if(new->data < root->lchild->data)
			root = avl_rotate_right(root);
		else if(new->data > root->lchild->data)
			root = avl_rotate_leftright(root);
	}

	else if(height(root->rchild) - height(root->lchild) == 2)
	{
		if(new->data > root->rchild->data)
			root = avl_rotate_left(root);
		else if(new->data < root->rchild->data)
			root = avl_rotate_rightleft(root);
	}


	root->height = MAX(height(root->lchild), height(root->rchild)) + 1;
	return root;
}

linktree avl_remove(linktree root, tn_datatype data)
{
	if(root == NULL)
		return NULL;

	if(data < root->data)
		root->lchild = avl_remove(root->lchild, data);
	else if(data > root->data)
		root->rchild = avl_remove(root->rchild, data);
	else
	{
		linktree p;

		if(root->lchild != NULL)
		{
			for(p=root->lchild; p->rchild!=NULL; p=p->rchild){;}
			root->data = p->data;
			root->lchild = avl_remove(root->lchild, p->data);
		}
		else if(root->rchild != NULL)
		{
			for(p=root->rchild; p->lchild!=NULL; p=p->lchild){;}
			root->data = p->data;
			root->rchild = avl_remove(root->rchild, p->data);
		}
		else
		{
			free(root);
			return NULL;
		}
	}

	if(height(root->lchild) - height(root->rchild) == 2)
	{
		if(height(root->lchild->rchild)-height(root->lchild->rchild) == 1)
			root = avl_rotate_leftright(root);
		else
			root = avl_rotate_right(root);
	}
	else if(height(root->rchild) - height(root->lchild) == 2)
	{
		if(height(root->rchild->lchild)-height(root->rchild->rchild) == 1)
			root = avl_rotate_rightleft(root);
		else
			root = avl_rotate_left(root);
	}

	root->height = MAX(height(root->lchild), height(root->rchild)) + 1;
	return root;
}

int main(void)
{
	linktree root = NULL;

	printf("输入大于0的数插入节点\n");
	printf("输入小于0的数删除节点\n");
	printf("输入0退出程序\n");

	int n;
	while(1)
	{
		scanf("%d", &n);

		if(n > 0)
		{
			linktree new = new_node(n);
			root = avl_insert(root, new);
		}
		else if(n < 0)
		{
			root = avl_remove(root, -n);
		}
		else
			break;

		draw(root);
		system("firefox -new-tab *.html &");
	}
	system("rm *.html");

	return 0;
}
