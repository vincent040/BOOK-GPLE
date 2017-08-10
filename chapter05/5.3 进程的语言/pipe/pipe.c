//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/pipe/pipe.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用无名管道pipe，实现父子进程间通信
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int fd[2];

	if(pipe(fd) == -1)
	{
		perror("pipe()");
		exit(1);
	}

	pid_t x = fork();

	if(x == 0)
	{
		char *s = "hello, I am your child\n";
		write(fd[1], s, strlen(s));
	}
	
	if(x > 0)
	{
		char buf[30];
		bzero(buf, 30);

		read(fd[0], buf, 30);
		printf("from child: %s", buf);
	}

	close(fd[0]);
	close(fd[1]);
	return 0;
}
