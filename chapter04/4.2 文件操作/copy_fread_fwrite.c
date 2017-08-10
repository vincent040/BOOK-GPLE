//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/copy_fread_fwrite.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用每次一个数据块的文件读写接口fgets()和fputs()
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

#define SIZE 100
#define NMEMB 5

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

	char buf[SIZE * NMEMB];
	int total = 0;
	long pos1, pos2;
	while(1)
	{
		bzero(buf, SIZE * NMEMB);
		pos1 = ftell(fp_src);
		if(fread(buf, SIZE, NMEMB, fp_src) < NMEMB)
		{
			if(feof(fp_src))
			{
				pos2 = ftell(fp_src);
				fwrite(buf, pos2-pos1, 1, fp_dst);
				total += (pos2 - pos1);

				printf("copy completed, %d bytes"
					" have been copied.\n", total);
				break;
			}
			else if(ferror(fp_src))
			{
				perror("fread()");
				break;
			}
		}

		fwrite(buf, SIZE, NMEMB, fp_dst);
		total += SIZE*NMEMB;
	}


	fclose(fp_src);
	fclose(fp_dst);

	return 0;
}
