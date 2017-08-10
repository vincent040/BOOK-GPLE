//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.3/check_LCD_thread.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 利用mmap()来给LCD设备映射一块显存，并在显存中每隔
//               一秒显示一种单色
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/fb.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <semaphore.h>
#include <sys/sem.h>
#include <pthread.h>

enum color{red, green, blue};
struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo;
unsigned long *pixel[3];
sem_t s;

unsigned long *create_pixel(struct fb_var_screeninfo *pinfo,
		   	    enum color c)
{
	unsigned long *pixel = calloc(1, pinfo->bits_per_pixel/8);
	unsigned long *mask  = calloc(1, pinfo->bits_per_pixel/8);
	*mask |= 0x1;

	int i;
	switch(c)
	{
	case red:
		for(i=0; i<pinfo->red.length-1; i++)
		{
			*mask <<= 1;
			*mask |= 0x1;
		}
		*pixel |= *mask << pinfo->red.offset;
		break;
	case green:
		for(i=0; i<pinfo->green.length-1; i++)
		{
			*mask <<= 1;
			*mask |= 0x1;
		}
		*pixel |= *mask << pinfo->green.offset;
		break;
	case blue:
		for(i=0; i<pinfo->blue.length-1; i++)
		{
			*mask <<= 1;
			*mask |= 0x1;
		}
		*pixel |= *mask << pinfo->blue.offset;
	}

	return pixel;
}

void *prefetch(void *arg)
{
	char *FB[] = {(char *)arg, (char *)arg + 800*480*4};
	unsigned long bpp = vinfo.bits_per_pixel;

	int k, i;
	for(k=0; ;k++)
	{
		for(i=0; i<vinfo.xres * vinfo.yres; i++)
		{
			memcpy(FB[k%2]+i*bpp/8, pixel[k%3], bpp/8);
		}
		sem_post(&s);
		sleep(1);
	}
}

int main(void)
{
	int lcd = open("/dev/fb0", O_RDWR);
	if(lcd == -1)
	{
		perror("open(\"/dev/fb0\")");
		exit(1);
	}

	ioctl(lcd, FBIOGET_FSCREENINFO, &finfo);
	ioctl(lcd, FBIOGET_VSCREENINFO, &vinfo);

	vinfo.xoffset = 0;
	vinfo.yoffset = 0;
	ioctl(lcd, FBIOPAN_DISPLAY, &vinfo);

	unsigned long bpp = vinfo.bits_per_pixel;

	pixel[0] = create_pixel(&vinfo, red);
	pixel[1] = create_pixel(&vinfo, green);
	pixel[2] = create_pixel(&vinfo, blue);


	char *FB = mmap(NULL, vinfo.xres*vinfo.yres_virtual * bpp/8,
			PROT_READ | PROT_WRITE, MAP_SHARED,
			lcd, 0);

	sem_init(&s, 0, 0);

	pthread_t tid;
	pthread_create(&tid, NULL, prefetch, (void *)FB);

	int offset[] = {0, 480};
	int k, i;
	for(k=0; ; k++)
	{
		vinfo.xoffset = 0;
		vinfo.yoffset = offset[k%2];
	
		sem_wait(&s);
		ioctl(lcd, FBIOPAN_DISPLAY, &vinfo);
	}

	return 0;
}
