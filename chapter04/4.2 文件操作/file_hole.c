//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/file_hole.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 利用函数lseek()制造文件空洞。
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
	int fd = open("file", O_RDWR|O_CREAT|O_TRUNC, 0644);

	write(fd, "abc", 3);
	lseek(fd, 100, SEEK_CUR);
	write(fd, "xyz", 3);

	int fd2 = open("a", O_CREAT|O_RDWR|O_TRUNC, 0644);
	lseek(fd, 0, SEEK_SET);
	char buf[20];
	int n;
	while(1)
	{
		bzero(buf, 20);
		n = read(fd, buf, 20);
		if(n == 0)
			break;

		write(fd2, buf, n);
	}

	close(fd);
	close(fd2);
	return 0;
}
