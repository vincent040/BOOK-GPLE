//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.3/animation/pic_show.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 显示一张RGB格式的图像
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4animation.h"

void write_lcd(int lcd, unsigned long (*image)[WIDTH])
{
	unsigned long (*FB)[WIDTH] = mmap(NULL, SCREEN_SIZE*4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);

	memcpy(FB, image, SCREEN_SIZE * 4);
}
