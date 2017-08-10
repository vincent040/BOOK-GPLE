//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.3/zero_array.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示柔型数组（零长数组）的定义和使用
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

struct node
{
	int msg_len;
	/************
	any other data
	*************/
	char msg[0];
};

void test_node(struct node *p);

int main(void)
{
	char buffer[100];

	while(1)
	{
		fgets(buffer, 100, stdin);

		struct node *p = malloc(sizeof(struct node)
				 	+ strlen(buffer)
					+ 1);

		p->msg_len = strlen(buffer) + 1;
		strncpy(p->msg, buffer, p->msg_len);

		test_node(p);
	}
	return 0;
}

void test_node(struct node *p)
{
	printf("total len: %d\n", sizeof(struct node)
				  + p->msg_len);

	printf("message: %s", p->msg);
}
