//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/copy_fgetc_fputc.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用每次一个字节的文件读写接口fgetc()和fputc()
//               实现对文件的复制操作。
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

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Usage: %s <src> <dst>\n", argv[0]);
		exit(1);
	}


	FILE *fp_src = fopen(argv[1], "r");
	FILE *fp_dst = fopen(argv[2], "w");


	if(fp_src == NULL || fp_dst == NULL)
	{
		perror("fopen()");
		exit(1);
	}

	int c, total = 0;
	while(1)
	{
		c = fgetc(fp_src);

		if(c == EOF && feof(fp_src))
		{
			printf("copy completed, "
				"%d bytes have been copied.\n", total);
			break;
		}
		else if(ferror(fp_src))
		{
			perror("fgetc()");
			break;
		}

		fputc(c, fp_dst);
		total++;
	}


	fclose(fp_src);
	fclose(fp_dst);

	return 0;
}
