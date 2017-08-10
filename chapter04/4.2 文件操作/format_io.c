//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/format_io.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了格式化IO函数的基本用法
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define NAMELEN 20

struct student
{
	char name[NAMELEN];
	char sex;
	int age;
	float stature;

	struct student *next;
};

struct student *init_list(void)
{
	struct student *head = malloc(sizeof(struct student));
	head->next = NULL;

	return head;
}


void add_student(struct student *head, struct student *new)
{
	struct student *tmp = head;

	while(tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = new;
}


void show_student(struct student *head)
{
	struct student *tmp = head->next;

	while(tmp != NULL)
	{
		fprintf(stdout, "%-5s %c %d %.1f\n",
			tmp->name, tmp->sex, tmp->age, tmp->stature);

		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	FILE *fp = fopen("format_data", "r");


	struct student *head = init_list();

	int count = 0;
	while(1)
	{
		struct student *new = malloc(sizeof(struct student));


		if(fscanf(fp, "%s %c %d %f",
			new->name, &(new->sex),
			&(new->age), &(new->stature)) == EOF)
		{
			break;
		}
			

		add_student(head, new);
		count++;
	}

	printf("%d students have been added.\n", count);
	show_student(head);

	fclose(fp);

	return 0;
}
