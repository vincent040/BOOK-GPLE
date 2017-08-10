//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.3/animation/left_2_right.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 图像显示算法（图片从左到右移动）
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4animation.h"

void left2right_in(int lcd, unsigned long (*image)[WIDTH])
{
	unsigned long (*FB)[WIDTH] = mmap(NULL, WIDTH * HEIGHT * 4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);
	int i, j;
	for(i=0; i<WIDTH; i++)
	{
		for(j=0; j<HEIGHT; j++)
		{
			memcpy(&FB[j][0],
				&image[j][WIDTH-1-i], 4*(i+1));
		}
	}
}

void left2right_out(int lcd, unsigned long (*image)[WIDTH])
{
	unsigned long (*FB)[WIDTH] = mmap(NULL, WIDTH * HEIGHT * 4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);
	int i, j;
	for(i=0; i<WIDTH; i++)
	{
		for(j=0; j<HEIGHT; j++)
		{
			memset(&FB[j][0], 0, 4*(i+1));
			memcpy(&FB[j][i+1],
				&image[j][0], (WIDTH-1-i)*4);
		}
	}
}

void left_2_right(int lcd, unsigned long (*image)[WIDTH])
{
	left2right_in(lcd, image);
	left2right_out(lcd, image);
}
