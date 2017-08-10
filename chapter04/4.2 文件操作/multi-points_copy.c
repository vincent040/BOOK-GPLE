//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/multi-points_copy.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 利用文件空洞，使用多进程同时操作一个文件
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


	pid_t a = fork();


	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644);
	if(fd1 == -1 || fd2 == -1)
	{
		perror("open()");
		exit(1);
	}

	int size = lseek(fd1, 0, SEEK_END);
	if(a == 0)
	{
		lseek(fd1, size/2, SEEK_SET);
		lseek(fd2, size/2, SEEK_SET);
	}
	else if(a > 0)
	{
		lseek(fd1, 0, SEEK_SET);
	}

	char buf[100];
	int nread;

	while(1)
	{
		bzero(buf, 100);
		nread = read(fd1, buf, 100);
		if(nread==0)
			break;

		if(a > 0)
		{
			int n;

			n = lseek(fd1, 0, SEEK_CUR) - size/2;
			if(n >= 0)
			{
				write(fd2, buf, n);
				exit(0);
			}
		}

		write(fd2, buf, nread);
	}

	close(fd1);
	close(fd2);

	return 0;
}
