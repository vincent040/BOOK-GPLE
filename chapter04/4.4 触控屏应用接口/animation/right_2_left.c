//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.4/animation/right_2_left.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 图像显示算法（图片从右向左移动）
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4animation.h"

void right2left_in(int lcd, unsigned long (*image)[WIDTH])
{
	unsigned long (*FB)[WIDTH] = mmap(NULL, WIDTH * HEIGHT * 4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);
	int i, j;
	for(i=0; i<WIDTH; i++)
	{
		for(j=0; j<HEIGHT; j++)
		{
			memcpy(&FB[j][WIDTH-i-1], &image[j][0],
							4*(i+1));
		}
		usleep(100);
	}
}

void right2left_out(int lcd, unsigned long (*image)[WIDTH])
{
	unsigned long (*FB)[WIDTH] = mmap(NULL, WIDTH * HEIGHT * 4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);
	int i, j;
	for(i=0; i<WIDTH; i++)
	{
		for(j=0; j<HEIGHT; j++)
		{
			memcpy(&FB[j][0], &image[j][i+1],
						(WIDTH-1-i)*4);
			memset(&FB[j][WIDTH-1-i], 0, (1)*4);
		}
		usleep(100);
	}
}

void right_2_left(int lcd, unsigned long (*image)[WIDTH])
{
	right2left_in(lcd, image);
	right2left_out(lcd, image);
}
