////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.5/moving_picture.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用tslib库API判断手指在触摸屏滑动的轨迹，SDL使用
//               这些坐标轨迹让图片位置做出相应的移动。
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <semaphore.h>

#include "tslib.h"
#include "SDL.h"

#define LCD_WIDTH  800
#define LCD_HEIGHT 480

SDL_Surface *screen = NULL;
SDL_Surface *image  = NULL;

int xoffset, yoffset;

sem_t s;

struct tsdev *init_ts(void)
{
	char *tsdevice = getenv("TSLIB_TSDEVICE");
	if(tsdevice == NULL)
	{
		tsdevice = "/dev/event0";
	}

	struct tsdev *ts = ts_open(tsdevice, 0);
	ts_config(ts);

	return ts;
}

void quit(int sig)
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(image);
	SDL_Quit();

	exit(0);
}

void read_moving(void *arg)
{
	struct tsdev *ts = NULL;
	struct ts_sample samp1;
	struct ts_sample samp2;

	bzero(&samp1, sizeof(samp1));
	bzero(&samp2, sizeof(samp2));

	// 初始化触摸屏
	ts = init_ts();

	while(1)
	{
		ts_read(ts, &samp1, 1);
		usleep(100);
		ts_read(ts, &samp2, 1);

		xoffset = samp2.x - samp1.x;
		yoffset = samp2.y - samp1.y;

		xoffset = xoffset>30||xoffset<-30 ? 0 : xoffset;
		yoffset = yoffset>30||yoffset<-30 ? 0 : yoffset;

		sem_post(&s);

		if(samp1.pressure == 0 | samp2.pressure == 0)
		{
			bzero(&samp1, sizeof(samp1));
			bzero(&samp2, sizeof(samp2));
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s <bmp-file>\n", argv[0]);
		exit(0);
	}

	signal(SIGINT, quit);

	// 初始化SDL视频子系统，并设置视窗surface的参数（与LCD一致）
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(LCD_WIDTH, LCD_HEIGHT,
						0, SDL_ANYFORMAT|SDL_SWSURFACE);

	// 装载BMP图片文件SDL表示没压力
	image = SDL_LoadBMP(argv[1]);

	// 1, image_offset规定了图片要显示的矩形部分
	// 2, background_offset规定了图像要显示在视窗的那个位置，其中：
	SDL_Rect image_offset;
	SDL_Rect backgroud_offset;
	bzero(&image_offset, sizeof(image_offset));
	bzero(&backgroud_offset, sizeof(backgroud_offset));
	printf("press ctrl+c to quit.\n");

	sem_init(&s, 0, 0);

	pthread_t tid;
	pthread_create(&tid, NULL, read_moving, NULL);

	// 1, x和y规定了图像要显示的矩形的左上角坐标
	// 2, w和h规定了以(x,y)为左上角的矩形的宽和高
	image_offset.x = 0;
	image_offset.y = 0;
	image_offset.w = 800;
	image_offset.h = 480;

	while(1)
	{
		// 产生一个RGB值为000（黑色）的像素
		uint32_t black_pixel = SDL_MapRGB(screen->format, 0, 0, 0);
		// 将屏幕刷成黑色
		SDL_FillRect(screen, &screen->clip_rect, black_pixel);
		// 将图像（image）blit到屏幕上（screen）
		long tmp1 = backgroud_offset.x;
		long tmp2 = backgroud_offset.y;
		SDL_BlitSurface(image, &image_offset, screen, &backgroud_offset);

		// 显示screen上的元素
		SDL_Flip(screen);

		// 1，x和y规定了图像surface放在视窗的左上角坐标
		// 2，w和h都是作废的。
		backgroud_offset.x = tmp1 + xoffset;
		backgroud_offset.y = tmp2 + yoffset;

		sem_wait(&s);
	}

	SDL_FreeSurface(screen);
	SDL_FreeSurface(image);
	SDL_Quit();

	return 0;
}