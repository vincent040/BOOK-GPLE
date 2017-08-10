//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.4/animation/head4animation.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 图像显示算法头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef _HEAD4ANIMATION_H_
#define _HEAD4ANIMATION_H_

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

#define SCREEN_SIZE 800*480
#define WIDTH  800
#define HEIGHT 480
#define BLIND  5

struct argument
{
	unsigned long (*FB)[WIDTH];
	unsigned long (*image)[WIDTH];
	int offset;
	int flag;
};

void falling_down_in(int lcd, unsigned long (*image)[WIDTH]);
void falling_down_out(int lcd, unsigned long (*image)[WIDTH]);
void falling_down(int lcd, unsigned long (*image)[WIDTH]);

void floating_up_in(int lcd, unsigned long (*image)[WIDTH]);
void floating_up_out(int lcd, unsigned long (*image)[WIDTH]);
void floating_up(int lcd, unsigned long (*image)[WIDTH]);

void left2right_in(int lcd, unsigned long (*image)[WIDTH]);
void left2right_out(int lcd, unsigned long (*image)[WIDTH]);
void left_2_right(int lcd, unsigned long (*image)[WIDTH]);

void right2left_in(int lcd, unsigned long (*image)[WIDTH]);
void right2left_out(int lcd, unsigned long (*image)[WIDTH]);
void right2left(int lcd, unsigned long (*image)[WIDTH]);

void blind_window_in(int lcd, unsigned long (*image)[WIDTH]);
void blind_window_out(int lcd, unsigned long (*image)[WIDTH]);
void blind_window(int lcd, unsigned long (*image)[WIDTH]);

#endif
