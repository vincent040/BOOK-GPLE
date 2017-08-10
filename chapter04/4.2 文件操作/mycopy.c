//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/mycopy.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 利用一个简单文件复制案例，演示了文件基本读写操作
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 50

int main(int argc, char **argv)
{
	int fd_from, fd_to;

	if(argc != 3)
	{
		printf("Uage: %s <src> <dst>", argv[0]);
		exit(1);
	}
	
	fd_from = open(argv[1], O_RDONLY);
	fd_to   = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);

	char buf[SIZE];
	char *p;
	int nread, nwrite;

	while(1)
	{

		while((nread=read(fd_from, buf, SIZE))==-1
			&& errno == EINTR){;}


		if(nread == -1)
		{
			perror("read() error");
			break;
		}

		if(nread == 0)
		{
			break;
		}

		p = buf;
		while(nread > 0)
		{

			while((nwrite=write(fd_to, p, SIZE))==-1
				&& errno == EINTR){;}


			if(nwrite == -1)
			{
				perror("write() error");
				break;
			}

			nread -= nwrite;
			p += nwrite;
		}
	}

	close(fd_from);
	close(fd_to);

	return 0;
}
