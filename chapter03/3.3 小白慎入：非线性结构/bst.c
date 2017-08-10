////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/bst.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: BST算法实现代码
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include "head4tree.h"
#include "drawtree.h"

linktree bst_insert(linktree root, linktree new)
{
	if(new == NULL)
		return root;

	if(root == NULL)
		return new;

	if(new->data > root->data)
	{
		root->rchild = bst_insert(root->rchild, new);
	}
	else if(new->data < root->data)
	{
		root->lchild = bst_insert(root->lchild, new);
	}
	else
	{
		printf("%d is already exist.\n", new->data);
	}

	return root;
}

linktree bst_find(linktree root, tn_datatype data)
{
	if(root == NULL)
		return NULL;

	if(data < root->data)
		return bst_find(root->lchild, data);
	else if(data > root->data)
		return bst_find(root->rchild, data);
	else
		return root;
}

linktree bst_remove(linktree root, tn_datatype n)
{
	if(root == NULL)
		return NULL;

	if(n < root->data)
		root->lchild = bst_remove(root->lchild, n);
	else if(n > root->data)
		root->rchild = bst_remove(root->rchild, n);
	else
	{
		linktree tmp;
		if(root->lchild != NULL)
		{
			for(tmp=root->lchild; tmp->rchild!=NULL;
			    tmp=tmp->rchild);

			root->data = tmp->data;
			root->lchild = bst_remove(root->lchild, tmp->data);
		}
		else if(root->rchild != NULL)
		{
			for(tmp=root->rchild; tmp->lchild!=NULL;
			    tmp=tmp->lchild);

			root->data = tmp->data;
			root->rchild = bst_remove(root->rchild, tmp->data);
		}
		else
		{
			free(root);
			return NULL;
		}
	}
	return root;
}

int main(void)
{
	linktree root;
	root = NULL;

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
			root = bst_insert(root, new);
		}
		else if(n < 0)
		{
			root = bst_remove(root, -n);
		}
		if(n == 0)
			break;

		draw(root);
		
		system("firefox -new-tab *.html &");
	}
	system("rm *.html");

	return 0;
}
