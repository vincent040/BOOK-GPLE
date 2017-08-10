////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.3/pic_show.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 直接显示一张bin格式的RGB图像
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

#define SCREEN_SIZE 800*480
#define WIDTH  800
#define HEIGHT 480

void write_lcd(char *p, int picfd)
{
	memset(p, 0, SCREEN_SIZE*4);

	int n, offset=0;
	while(1)
	{
		n = read(picfd, p+offset, SCREEN_SIZE*4);
		if(n <= 0)
			break;
		offset += n;
	}
}

int main(void)
{
	int lcd = open("/dev/fb0", O_RDWR);
	if(lcd == -1)
	{
		perror("open()");
		exit(1);
	}

	char *p = mmap(NULL, SCREEN_SIZE*4,
			PROT_READ | PROT_WRITE,
			MAP_SHARED, lcd, 0);

	int picfd = open("image.bin", O_RDONLY);
	if(picfd == -1)
	{
		perror("open()");
		exit(1);
	}
	write_lcd(p, picfd);

	return 0;
}
