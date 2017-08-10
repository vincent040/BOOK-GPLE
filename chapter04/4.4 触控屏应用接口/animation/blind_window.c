//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.4/animation/blind_window.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 图像显示算法（百叶窗）
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "head4animation.h"

#define IN  1
#define OUT 0

void *routine(void *p)
{
	struct argument *arg = (struct argument *)p;

	int i;

	if(arg->flag == IN)
	{
		for(i=HEIGHT/BLIND-1; i>=0; i--)
		{
			memcpy(&(arg->FB)[arg->offset+i][0],
		 	       &(arg->image)[arg->offset+i][0],
			       WIDTH*4);

			usleep(10000);
		}
	}

	if(arg->flag == OUT)
	{
		for(i=0; i<HEIGHT/BLIND; i++)
		{
			memset(&(arg->FB)[arg->offset+i][0], 0, WIDTH*4);

			usleep(10000);
		}
	}

	pthread_exit(NULL);
}

void __write_lcd(int lcd, unsigned long (*image)[WIDTH], int flag)
{
	unsigned long (*p)[WIDTH] = mmap(NULL, WIDTH * HEIGHT * 4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);
	int i;
	pthread_t tid[BLIND];
	for(i=0; i<BLIND; i++)
	{
		struct argument *arg =
				malloc(sizeof(struct argument));
		arg->FB = p;
		arg->image = image;
		arg->offset = i*(HEIGHT/BLIND);
		arg->flag = flag;


		pthread_create(&tid[i], NULL, routine, (void *)arg);
	}

	for(i=0; i<BLIND; i++)
	{
		pthread_join(tid[i], NULL);
	}
}

void blind_window_in(int lcd, unsigned long (*image)[WIDTH])
{
	__write_lcd(lcd, image, IN); 
}

void blind_window_out(int lcd, unsigned long (*image)[WIDTH])
{
	__write_lcd(lcd, image, OUT); 
}

void blind_window(int lcd, unsigned long (*image)[WIDTH])
{
	blind_window_in(lcd, image);
	blind_window_out(lcd, image);
}
