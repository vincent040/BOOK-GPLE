//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/mmap.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了函数mmap的基本用法
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		exit(1);
	}


	int fd = open(argv[1], O_RDONLY);


	char *p = mmap(NULL, 1024, PROT_READ,
				MAP_PRIVATE, fd, 0);


	printf("%s\n", p);
	
	
	return 0;
}
