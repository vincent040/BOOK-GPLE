//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/fopen_fclose.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了fopen()和fclose()的基本用法
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	FILE *fp = fopen("a.txt", "r+");


	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	
	if(fclose(fp) == EOF)
	{
		perror("fclose()");
		exit(1);
	}

	return 0;
}
