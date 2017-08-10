//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch02/2.5/struct.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了结构体的特性和使用细节
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

struct student
{
	char name[32];
	int age;
	float score;
};

void show(struct student someone);

int main(void)
{
	struct student Jack;
	strcpy(Jack.name, "Jack");
	Jack.age = 18;
	Jack.score = 90.5;

	struct student Rose = {"Rose", 16, 80.0};

	struct student Michael = {
				.score = 88.5,
				.name = "Michael"
			      };


	struct student Michael_Junior;
	Michael_Junior = Michael;


	struct student myclass[50];
	myclass[0] = Jack;
	myclass[1] = Rose;
	myclass[2] = Michael;


	struct student *p;
	p = &Michael;


	(*p).age = 23;
	p -> age = 23;

	show(Michael);
	return 0;
}

void show(struct student someone)
{
	printf("name: %s, age: %d, score: %f\n",
		someone.name,
		someone.age,
		someone.score);
}
