//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.1/singly_circle_list.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 单向循环链表的实现及其操作细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define SIZE 20

typedef struct node
{
	int data;
	struct node *next;
}listnode, *linklist;

linklist init_list(void)
{
	linklist mylist = malloc(sizeof(listnode));
	mylist->next = mylist;

	return mylist;
}

bool is_empty(linklist mylist)
{
	return mylist->next == mylist;
}

linklist new_node(int data, linklist next)
{
	linklist new = malloc(sizeof(listnode));

	if(new != NULL)
	{
		new->data = data;
		new->next = next;
	}

	return new;
}

void insert_node(linklist p, linklist new)
{
	if(p == NULL || new == NULL)
		return;

	new->next = p->next;
	p->next = new;
}

void remove_node(linklist delete)
{
	linklist tmp = delete;
	while(tmp->next != delete)
	{
		tmp = tmp->next;
	}

	tmp->next = delete->next;
	delete->next = NULL;
}

void move_node(linklist p, linklist anchor)
{
	if(p == NULL || anchor == NULL)
		return;

	remove_node(p);
	insert_node(anchor, p);
}

linklist find_node(linklist mylist, int data)
{
	if(is_empty(mylist))
		return NULL;

	linklist tmp;

	for(tmp=mylist->next; tmp!=mylist; tmp=tmp->next)
	{
		if(data == tmp->data)
			break;
	}
	return tmp==mylist ? NULL : tmp;
}


int parse(char buf[SIZE], int number[2])
{
	if(!strcmp(buf, "\n"))
		return 0;

	int count = 1;
	char *p, delim[] = ", ";

	p = strtok(buf, delim);
	number[0] = atoi(p);
	
	p = strtok(NULL, delim);
	if(p != NULL)
	{
		number[1] = atoi(p);
		count++;
	}
	
	return count;
}


void show(linklist mylist)
{
	if(is_empty(mylist))
		return;

	linklist p = mylist->next;

	int i = 0;
	while(p != mylist)
	{

		printf("%s%d", i==0 ? "" : " --> ", p->data);
		p = p->next;
		i++;
	}

	printf("\n");
}

int main(void)
{
	linklist mylist = init_list();

	int ret, number[2];
	char buf[SIZE];

	while(1)
	{
		bzero(buf, SIZE);
		fgets(buf, SIZE, stdin);
		ret = parse(buf, number);


		if(ret == 0)
		{
			continue;
		}


		if(ret == 1 && number[0] > 0)
		{
			linklist new = new_node(number[0], NULL);
			insert_node(mylist, new);
			show(mylist);
		}


		else if(ret == 1 && number[0] < 0)
		{
			linklist delete = find_node(mylist, -number[0]);
			if(delete == NULL)
			{
				printf("%d is NOT found.\n", -number[0]);
				show(mylist);
				continue;
			}
	
			remove_node(delete);
			show(mylist);
		}

		else if(ret == 2)
		{
			linklist pa = find_node(mylist, number[0]);
			linklist pb = find_node(mylist, number[1]);
	
			if(pa == NULL || pb == NULL)
			{
				printf("node does NOT exist.\n");
				show(mylist);
				continue;
			}
	
			move_node(pa, pb);
			show(mylist);
		}
		else
			break;
	}
	return 0;
}
