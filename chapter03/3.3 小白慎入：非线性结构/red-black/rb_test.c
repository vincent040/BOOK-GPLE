//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/rb_test.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用红黑树操作接口实现的测试代码，测试结果用网页
//               展示。
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

		if(n < 0)
		{
			rb_delete(&root, -n);
		}
		else if(n > 0)
		{
			linktree new = new_node(n);
			rb_insert(&root, new);
		}
		else
			break;

		draw(root);
		system("firefox *.html &");
	}

	system("rm *.html");

	return 0;
}
