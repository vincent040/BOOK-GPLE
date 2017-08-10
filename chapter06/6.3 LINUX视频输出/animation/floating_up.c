//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.3/animation/floating_up.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 图像显示算法（图片上浮）
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4animation.h"

void floating_up_in(int lcd, unsigned long (*image)[WIDTH])
{
	unsigned long (*FB)[WIDTH] = mmap(NULL, WIDTH * HEIGHT * 4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);
	int i = 0;
	while(1)
	{
		memcpy(&FB[HEIGHT-i-1][0], &image[0][0],
						WIDTH*4*(i+1));
		if(i >= HEIGHT-1)
			break;

		usleep(1000);
		i++;
	}
}

void floating_up_out(int lcd, unsigned long (*image)[WIDTH])
{
	unsigned long (*FB)[WIDTH] = mmap(NULL, WIDTH * HEIGHT * 4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);
	int i;
	for(i=0; i<=HEIGHT; i++)
	{
		memset(&FB[HEIGHT-i][0], 0, WIDTH*4*i);
		memcpy(&FB[0][0], &image[i][0],
					WIDTH*4*(HEIGHT-i));
		usleep(1000);
	}
}

void floating_up(int lcd, unsigned long (*image)[WIDTH])
{
	floating_up_in(lcd, image);
	floating_up_out(lcd, image);
}
