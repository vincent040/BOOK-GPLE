////////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch06/6.5/v4l2_yuv_videostream.c  
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用SDL处理从摄像头捕获的YUV视频流数据
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include <linux/fb.h>
#include <linux/videodev2.h>
#include <linux/input.h>
#include <sys/ioctl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <setjmp.h>

#include <SDL.h>
#include <SDL_thread.h>

#define LCD_WIDTH  800
#define LCD_HEIGHT 480


int shooting(char *yuvdata, int size, SDL_Overlay *bmp,
			int width, int height)
{
	SDL_LockYUVOverlay(bmp);
	memcpy(bmp->pixels[0], yuvdata, size);
	bmp->pitches[0] = width;
	SDL_UnlockYUVOverlay(bmp);

	SDL_Rect rect;
	rect.x = (LCD_WIDTH - width) / 2;
	rect.y = (LCD_HEIGHT - height) / 2;
	rect.w = width;
	rect.h = height;

	SDL_DisplayYUVOverlay(bmp, &rect);
}


void show_camfmt(struct v4l2_format *fmt)
{
	printf("camera width : %d \n", fmt->fmt.pix.width);
	printf("camera height: %d \n", fmt->fmt.pix.height);

	switch(fmt->fmt.pix.pixelformat)
	{
	case V4L2_PIX_FMT_JPEG:
		printf("camera pixelformat: V4L2_PIX_FMT_JPEG\n");
		break;
	case V4L2_PIX_FMT_YUYV:
		printf("camera pixelformat: V4L2_PIX_FMT_YUYV\n");
	}
}


int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s </dev/videoX>\n", argv[0]);
		exit(0);
	}

	// 打开LCD设备
	int lcd = open("/dev/fb0", O_RDWR);

	// // 获取LCD显示器的设备参数
	struct fb_var_screeninfo lcdinfo;
	ioctl(lcd, FBIOGET_VSCREENINFO, &lcdinfo);

	// 打开摄像头设备文件
	int cam_fd = open(argv[1], O_RDWR);

	struct v4l2_fmtdesc *a = calloc(1, sizeof(*a));
	a->index = 0;
	a->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	int ret;
	while((ret=ioctl(cam_fd, VIDIOC_ENUM_FMT, a)) == 0)
	{
		a->index++;
		printf("pixelformat: \"%c%c%c%c\"\n",
				(a->pixelformat >> 0) & 0XFF,
				(a->pixelformat >> 8) & 0XFF,
				(a->pixelformat >>16) & 0XFF,
				(a->pixelformat >>24) & 0XFF);

		printf("description: %s\n", a->description);
	}

	// 获取摄像头设备的功能参数(这一步可以不要)
	struct v4l2_capability cap;
	ioctl(cam_fd, VIDIOC_QUERYCAP, &cap);

	// 获取摄像头当前的采集格式
	struct v4l2_format *fmt = calloc(1, sizeof(*fmt));
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(cam_fd, VIDIOC_G_FMT, fmt) == -1)
	{
		fprintf(stderr, "[%s][%s][%d]: ioctl() failed: %s\n",
			__FILE__, __FUNCTION__, __LINE__, strerror(errno));
		exit(0);
	}
	show_camfmt(fmt);

	// 配置摄像头的采集格式
	bzero(fmt, sizeof(*fmt));
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt->fmt.pix.width = lcdinfo.xres;
	fmt->fmt.pix.height = lcdinfo.yres;
	fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;
	if(ioctl(cam_fd, VIDIOC_S_FMT, fmt) == -1)
	{
		fprintf(stderr, "[%s][%s][%d]: ioctl() failed: %s\n",
			__FILE__, __FUNCTION__, __LINE__, strerror(errno));
		exit(0);
	}

	// 设置即将要申请的摄像头缓存的参数
	int nbuf = 3;

	struct v4l2_requestbuffers reqbuf;
	bzero(&reqbuf, sizeof (reqbuf));
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuf.memory = V4L2_MEMORY_MMAP;
	reqbuf.count = nbuf;

	// 使用该参数reqbuf来申请缓存
	ioctl(cam_fd, VIDIOC_REQBUFS, &reqbuf);

	// 根据刚刚设置的reqbuf.count的值，来定义相应数量的struct v4l2_buffer
	// 每一个struct v4l2_buffer对应内核摄像头驱动中的一个缓存
	struct v4l2_buffer buffer[nbuf];
	int length[nbuf];
	unsigned char *start[nbuf];

	unsigned int i;
	for(i=0; i<nbuf; i++)
	{
		bzero(&buffer[i], sizeof(buffer[i]));
		buffer[i].type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buffer[i].memory = V4L2_MEMORY_MMAP;
		buffer[i].index = i;
		ioctl(cam_fd, VIDIOC_QUERYBUF, &buffer[i]);

		length[i] = buffer[i].length;
		start[i] = mmap(NULL, buffer[i].length,	PROT_READ | PROT_WRITE,
				  MAP_SHARED,	cam_fd, buffer[i].m.offset);

		ioctl(cam_fd , VIDIOC_QBUF, &buffer[i]);
	}

	// 启动摄像头数据采集
	enum v4l2_buf_type vtype= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(cam_fd, VIDIOC_STREAMON, &vtype);

	struct v4l2_buffer v4lbuf;
	bzero(&v4lbuf, sizeof(v4lbuf));
	v4lbuf.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4lbuf.memory= V4L2_MEMORY_MMAP;

	// *********** 设置SDL，为显示视频做准备 **************** //
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);

	SDL_Surface *screen = NULL;
	SDL_Overlay *bmp    = NULL;
	screen = SDL_SetVideoMode(LCD_WIDTH, LCD_HEIGHT, 0, 0);
	bmp    = SDL_CreateYUVOverlay(fmt->fmt.pix.width, 
		                          fmt->fmt.pix.height,
								  SDL_YUY2_OVERLAY, screen);
	// ****************************************************** //
	i = 0;
	while(1)
	{
		// 从队列中取出填满数据的缓存
		v4lbuf.index = i%nbuf;
		ioctl(cam_fd , VIDIOC_DQBUF, &v4lbuf); // VIDIOC_DQBUF在摄像头没数据的时候会阻塞

		//shooting(start[i%nbuf], length[i%nbuf], fb_mem,
		shooting(start[i%nbuf], length[i%nbuf],
			bmp, fmt->fmt.pix.width, fmt->fmt.pix.height);

	 	// 将已经读取过数据的缓存块重新置入队列中 
		v4lbuf.index = i%nbuf;
		ioctl(cam_fd , VIDIOC_QBUF, &v4lbuf);

		i++;
	}

	return 0;
}

