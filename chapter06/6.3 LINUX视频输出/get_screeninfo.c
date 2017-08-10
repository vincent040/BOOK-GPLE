////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.3/get_screeninfo.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 获取LCD设备硬件参数
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

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

void show_fix_screeninfo(struct fb_fix_screeninfo *p)
{
	printf("=== FIX SCREEN INFO === \n");

	printf("\tid: %s\n", p->id);
	printf("\tsmem_start: %#x\n", p->smem_start);
	printf("\tsmem_len: %u bytes\n", p->smem_len);

	printf("\ttype:");
	switch(p->type)
	{
	case FB_TYPE_PACKED_PIXELS:
		printf("PACKED_PIXELS\n");break;
	case FB_TYPE_PLANES:
		printf("PLANES\n");break;
	case FB_TYPE_INTERLEAVED_PLANES:
		printf("INTERLEAVED_PLANES\n");break;
	case FB_TYPE_TEXT:
		printf("TEXT\n");break;
	case FB_TYPE_VGA_PLANES:
		printf("VGA_PLANES\n");break;
	}

	printf("\tvisual:");
	switch(p->visual)
	{
	case FB_VISUAL_MONO01:
		printf("MONO01\n");break;
	case FB_VISUAL_MONO10:
		printf("MONO10\n");break;
	case FB_VISUAL_TRUECOLOR:
		printf("TRUECOLOR\n");break;
	case FB_VISUAL_PSEUDOCOLOR:
		printf("PSEUDOCOLOR\n");break;
	case FB_VISUAL_DIRECTCOLOR:
		printf("DIRECTCOLOR\n");break;
	case FB_VISUAL_STATIC_PSEUDOCOLOR:
		printf("STATIC_PSEUDOCOLOR\n");break;
	}

	printf("\txpanstep: %u\n", p->xpanstep);
	printf("\typanstep: %u\n", p->ypanstep);
	printf("\tywrapstep: %u\n", p->ywrapstep);
	printf("\tline_len: %u bytes\n", p->line_length);

	printf("\tmmio_start: %#x\n", p->mmio_start);
	printf("\tmmio_len: %u bytes\n", p->mmio_len);

	printf("\taccel: ");
	switch(p->accel)
	{
	case FB_ACCEL_NONE: printf("none\n"); break;
	default: printf("unkown\n");
	}

	printf("\n");
}

void show_var_screeninfo(struct fb_var_screeninfo *p)
{
	printf("=== VAR SCREEN INFO === \n");

	printf("\thsync_len: %u\n", p->hsync_len);
	printf("\tvsync_len: %u\n", p->vsync_len);
	printf("\tvmode: %u\n", p->vmode);

	printf("\tvisible screen size: %ux%u\n",
				p->xres, p->yres);
	printf("\tvirtual screen size: %ux%u\n\n",
				p->xres_virtual,
				p->yres_virtual);

	printf("\tbits per pixel: %u\n", p->bits_per_pixel);
	printf("\tactivate: %u\n\n", p->activate);

	printf("\txoffset: %d\n", p->xoffset);
	printf("\tyoffset: %d\n", p->yoffset);

	printf("\tcolor bit-fields:\n");
	printf("\tR: [%u:%u]\n", p->red.offset,
			       p->red.offset+p->red.length-1);
	printf("\tG: [%u:%u]\n", p->green.offset,
			       p->green.offset+p->green.length-1);
	printf("\tB: [%u:%u]\n\n", p->blue.offset,
			       p->blue.offset+p->blue.length-1);

	printf("\n");
}

int main(void)
{
	int lcd = open("/dev/fb0", O_RDWR|O_EXCL);
	if(lcd == -1)
	{
		perror("open()");
		exit(1);
	}

	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;

	ioctl(lcd, FBIOGET_FSCREENINFO, &finfo);
	ioctl(lcd, FBIOGET_VSCREENINFO, &vinfo);

	show_fix_screeninfo(&finfo);
	show_var_screeninfo(&vinfo);


	unsigned long WIDTH  = vinfo.xres;
	unsigned long HEIGHT = vinfo.yres;
	unsigned long VWIDTH  = vinfo.xres_virtual;
	unsigned long VHEIGHT = vinfo.yres_virtual;
	unsigned long BPP = vinfo.bits_per_pixel;

	char *p = mmap(NULL, VWIDTH * VHEIGHT * BPP/8,
			PROT_READ|PROT_WRITE,
			MAP_SHARED, lcd, 0);

	int image = open("images/girl.bin", O_RDWR);
	int image_size = lseek(image, 0L, SEEK_END);
	lseek(image, 0L, SEEK_SET);
	read(image, p, image_size);


	vinfo.xoffset = 0;
	vinfo.yoffset = 0;
	if(ioctl(lcd, FB_ACTIVATE_NOW, &vinfo))
	{
		perror("ioctl()");
	}
	ioctl(lcd, FBIOPAN_DISPLAY, &vinfo);

	sleep(1);

	vinfo.xoffset = 0;
	vinfo.yoffset = 100;
	if(ioctl(lcd, FB_ACTIVATE_NOW, &vinfo))
	{
		perror("ioctl()");
	}
	show_var_screeninfo(&vinfo);
	ioctl(lcd, FBIOPAN_DISPLAY, &vinfo);

	return 0;
}
