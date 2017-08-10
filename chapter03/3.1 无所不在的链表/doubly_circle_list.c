//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.1/doubly_circle_list.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 程序一开始自动初始化一个空双循环链表，用户输入一
//               个正整数则将该节点插入链表的末尾，用户输入一个负
//               整数则删除其绝对值对应的节点，用户若输入100,i200
//               则将节点100移动到200的前面，用户若输入100,200i则
//               将节点100移动到200的后面，用户输入0则退出程序。
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "commonheader.h"

#define SIZE 20
enum {insert, delete, move_p, move_n, quit};

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}listnode, *linklist;


linklist init_list(void)
{
	linklist mylist = malloc(sizeof(listnode));
	if(mylist != NULL)
	{
		mylist->prev = mylist->next = mylist;
	}
	return mylist;
}


linklist new_node(int data)
{
	linklist new = malloc(sizeof(listnode));
	if(new != NULL)
	{
		new->data = data;
		new->prev = new->next = NULL;
	}
	return new;
}


bool is_empty(linklist mylist)
{
	return mylist->prev == mylist->next;
}


void insert_prev(linklist new, linklist anchor)
{
	if(new == NULL || anchor == NULL)
		return;

	new->prev = anchor->prev;
	new->next = anchor;

	anchor->prev = new;
	new->prev->next = new;
}


void insert_next(linklist new, linklist anchor)
{
	if(new == NULL || anchor == NULL)
		return;

	new->prev = anchor;
	new->next = anchor->next;

	anchor->next = new;
	new->next->prev = new;
}


void remove_node(linklist delete)
{
	if(delete == NULL)
		return;

	delete->prev->next = delete->next;
	delete->next->prev = delete->prev;

	delete->prev = NULL;
	delete->next = NULL;
}


void move_prev(linklist p, linklist anchor)
{
	remove_node(p);
	insert_prev(p, anchor);
}


void move_next(linklist p, linklist anchor)
{
	remove_node(p);
	insert_next(p, anchor);
}


void show(linklist mylist)
{
	linklist tmp = mylist->next;

	int flag = 0;
	while(tmp != mylist)
	{
		printf("%s", flag==0 ? "" : "-->");
		printf("%d", tmp->data);

		tmp = tmp->next;
		flag = 1;
	}
	printf("\n");
}


linklist find_node(int data, linklist mylist)
{
	if(is_empty(mylist))
		return NULL;

	linklist tmp = mylist->next;

	while(tmp != mylist)
	{
		if(tmp->data == data)
			return tmp;

		tmp=tmp->next;
	}
	return NULL;
}


int parse(char buf[SIZE], int number[2])
{
	if(!strcmp(buf, "\n"))
		return 0;

	char *p, delim[] = ", ";

	p = strtok(buf, delim);
	number[0] = atoi(p);

	if(number[0] == 0)
		return quit;
	
	p = strtok(NULL, delim);
	if(p != NULL)
	{
		if(p[0] == 'i')
		{
			number[1] = atoi(p+1);
			return move_p;
		}
		else
		{
			number[1] = atoi(p);
			return move_n;
		}
	}

	return (number[0] > 0) ? insert : delete;
}

int main(void)
{
	linklist mylist;
	mylist = init_list();

	char buf[SIZE];
	int number[2], ret;
	while(1)
	{
		bzero(buf, SIZE);
		bzero(number, 2);

		fgets(buf, SIZE, stdin);
		ret = parse(buf, number);

		linklist new, tmp, p1, p2;
		switch(ret)
		{
		case insert:
			new = new_node(number[0]);
			insert_prev(new, mylist);
			break;

		case delete:
			tmp = find_node(-number[0], mylist);
			remove_node(tmp);
			free(tmp);
			break;

		case move_p:
			p1 = find_node(number[0], mylist);
			p2 = find_node(number[1], mylist);
			move_prev(p1, p2);
			break;

		case move_n:
			p1 = find_node(number[0], mylist);
			p2 = find_node(number[1], mylist);
			move_next(p1, p2);
			break;

		case quit:
			exit(0);
		}
		
		show(mylist);
	}

	return 0;
}
