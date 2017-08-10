//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.1/singly_list.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 单向链表的实现及其操作细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////


#define SIZE 20

typedef int datatype;

typedef struct node
{
	datatype data;
	struct node *next;
}listnode, *singly_list;

singly_list init_list(void)
{
	singly_list mylist = malloc(sizeof(listnode));
	if(mylist != NULL)
	{
		mylist->next = NULL;
	}

	return mylist;
}

bool is_empty(singly_list list)
{
	return list->next == NULL;
}

singly_list new_node(datatype data, singly_list next)
{
	singly_list new = malloc(sizeof(listnode));

	if(new != NULL)
	{
		new->data = data;
		new->next = next;
	}

	return new;
}

void insert_node(singly_list p, singly_list new)
{
	if(p == NULL || new == NULL)
		return;

	new->next = p->next;
	p->next = new;
}

bool remove_node(singly_list mylist, singly_list delete)
{
	if(is_empty(mylist))
		return false;

	singly_list p = mylist;
	while(p != NULL && p->next != delete)
	{
		p = p->next;
	}

	if(p == NULL)
		return false;

	p->next = delete->next;
	delete->next = NULL;

	return true;
}

void move_node(singly_list mylist, singly_list p, singly_list anchor)
{
	if(mylist == NULL || p == NULL || anchor == NULL)
		return;

	remove_node(mylist, p);
	insert_node(anchor, p);
}

void show(singly_list list)
{
	if(is_empty(list))
		return;

	singly_list p = list->next;

	int i = 0;
	while(p != NULL)
	{

		printf("%s%d", i==0 ? "" : " --> ", p->data);
		p = p->next;
		i++;
	}

	printf("\n");
}

singly_list find_node(singly_list mylist, datatype data)
{
	if(is_empty(mylist))
		return NULL;

	singly_list p;

	for(p=mylist->next; p != NULL; p=p->next)
	{
		if(p->data == data)
			break;
	}

	return p;
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

int main(void)
{
	singly_list mylist = init_list();

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
			singly_list new = new_node(number[0], NULL);
			insert_node(mylist, new);
			show(mylist);
		}


		else if(ret == 1 && number[0] < 0)
		{
			singly_list delete = find_node(mylist, -number[0]);
			if(delete == NULL)
			{
				printf("%d is NOT found.\n", -number[0]);
				show(mylist);
				continue;
			}
	
			remove_node(mylist, delete);
			show(mylist);
		}

		else if(ret == 2)
		{
			singly_list pa = find_node(mylist, number[0]);
			singly_list pb = find_node(mylist, number[1]);
	
			if(pa == NULL || pb == NULL)
			{
				printf("node does NOT exist.\n");
				show(mylist);
				continue;
			}
	
			move_node(mylist, pa, pb);
			show(mylist);
		}
		else
			break;
	}
	return 0;
}
