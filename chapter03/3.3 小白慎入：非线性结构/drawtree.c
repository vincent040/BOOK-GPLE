////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch03/3.3/drawtree.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 将二叉树的逻辑层次结构，用网页展示出来
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include "head4tree.h"
#include "drawtree.h"

void putunderline(int fd, int num)
{
	int i;
	for(i=0; i<num; i++)
	{
		write(fd, underline, strlen(underline));
	}
}


void putspace(int fd, int num)
{
	int i;
	for(i=0; i<num; i++)
	{
		write(fd, space, strlen(space));
	}
}

#ifdef RB
void putdata(int fd, linktree p)
{
	char s[50];
	bzero(s, 50);

	snprintf(s, 50, "%d", p->data);

	switch(p->color)
	{
	case RED:
		write(fd, data_begin_red, strlen(data_begin_red));
		write(fd, s, strlen(s));
		write(fd, data_end_red, strlen(data_end_red));
		break;
	case BLACK:
		write(fd, data_begin_blk, strlen(data_begin_blk));
		write(fd, s, strlen(s));
		write(fd, data_end_blk, strlen(data_end_blk));
	}
}
#else
void putdata(int fd, int data)
{
	char s[50];
	bzero(s, 50);

	snprintf(s, 50, "%d", data);
	write(fd, data_begin, strlen(data_begin));
	write(fd, s, strlen(s));
	write(fd, data_end, strlen(data_end));
}
#endif

static int Index = 0;
void create_index(linktree root)
{
	if(Index >= MAX_NODES_NUMBER-1)
		return;

	central_order[Index++] = root->data;
}


int get_index(tn_datatype data)
{
	int i;
	for(i=0; i<100; i++)
	{
		if(central_order[i] == data)
			return i;
	}
	return -1;
}


void data_leftside(int fd, linktree root, int spaces)
{
	if(root == NULL)
		return;

	int s_line=0;

	if(root->lchild != NULL)
	{
		s_line = get_index(root->data)-
			 get_index(root->lchild->data)-1;
	}
	putspace(fd, spaces-s_line);
	putunderline(fd, s_line);
}


int data_rightside(int fd, linktree root)
{
	if(root == NULL)
		return 0;

	int s_line=0;

	if(root->rchild != NULL)
	{
		s_line = get_index(root->rchild->data)-
			 get_index(root->data)-1;
	}

	putunderline(fd, s_line);
	return s_line;
}


void start_page(int fd)
{
	write(fd, page_begin, strlen(page_begin));
}


void end_page(int fd)
{
	write(fd, page_end, strlen(page_end));
}


void draw(linktree root)
{
	if(root == NULL)
		return;

	time_t t;
	time(&t);
	static char filename[FILENAME];
	bzero(filename, FILENAME);
	snprintf(filename, FILENAME, "%u.html", (unsigned)t);
	int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if(fd == -1)
	{
		perror("open() failed");
		exit(1);
	}

	Index = 0;
	mid_travel(root, create_index);

	linkqueue q = init_queue();

	linktree tmp = root;
	int ndata = 1;

	start_page(fd);
	while(1)
	{
		write(fd, line_begin, strlen(line_begin));

		int i, n = 0;
		int nextline = 0;
		for(i=0; i<ndata; i++)
		{
			int index = get_index(tmp->data);

			data_leftside(fd, tmp, index-n);

			#ifdef RB
			putdata(fd, tmp);
			#else
			putdata(fd, tmp->data);
			#endif
			int rightline = data_rightside(fd, tmp);

			if(tmp->lchild != NULL)
			{
				nextline++;
				en_queue(q, tmp->lchild);
			}
			if(tmp->rchild != NULL)
			{
				nextline++;
				en_queue(q, tmp->rchild);
			}
			if(!out_queue(q, &tmp))
				return;

			n = index + rightline;
			n++;
		}
		write(fd, line_end, strlen(line_end));
		ndata = nextline;
	}
	end_page(fd);
	close(fd);
}
