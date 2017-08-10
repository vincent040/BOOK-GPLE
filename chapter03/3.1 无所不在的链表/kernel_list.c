//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.1/kernel_list.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 用内核链表改造的doubly_circle_list.c，用户输入一
//               个正整数则将该节点插入链表的末尾，用户输入一个负
//               整数则删除其绝对值对应的节点，用户若输入100,i200
//               则将节点100移动到200的前面，用户若输入100,200i则
//               将节点100移动到200的后面，用户输入0则退出程序。
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "commonheader.h"
#include "list.h"

#define SIZE 20
enum {insert, delete, move_p, move_n, quit};

typedef struct node
{
	int data;
	struct list_head list;
}listnode, *linklist;


linklist init_list(void)
{
	linklist mylist = malloc(sizeof(listnode));
	if(mylist != NULL)
	{
		INIT_LIST_HEAD(&mylist->list);
	}
	return mylist;
}


linklist new_node(int data)
{
	linklist new = malloc(sizeof(listnode));
	if(new != NULL)
	{
		new->data = data;
		new->list.prev = LIST_POISON1;
		new->list.next = LIST_POISON2;
	}
	return new;
}

void show(linklist mylist)
{
	linklist tmp;
	struct list_head *pos;
	int flag = 0;

	list_for_each(pos, &mylist->list)
	{
		tmp = list_entry(pos, listnode, list);
		printf("%s", flag==0 ? "" : "-->");
		printf("%d", tmp->data);

		flag = 1;
	}
	printf("\n");
}


linklist find_node(int data, linklist mylist)
{
	if(list_empty(&mylist->list))
		return NULL;

	linklist pos;

	list_for_each_entry(pos, &mylist->list, list)
	{
		if(pos->data == data)
			return pos;
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
			list_add_tail(&new->list, &mylist->list);
			break;

		case delete:
			tmp = find_node(-number[0], mylist);
			list_del(&tmp->list);
			free(tmp);
			break;

		case move_p:
			p1 = find_node(number[0], mylist);
			p2 = find_node(number[1], mylist);
			list_move_tail(&p1->list, &p2->list);
			break;

		case move_n:
			p1 = find_node(number[0], mylist);
			p2 = find_node(number[1], mylist);
			list_move(&p1->list, &p2->list);
			break;

		case quit:
			exit(0);
		}
		
		show(mylist);
	}

	return 0;
}
