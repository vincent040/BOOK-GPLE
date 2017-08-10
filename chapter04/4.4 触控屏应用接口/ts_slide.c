//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.4/ts_slide.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 通过触摸屏显示上/下一张JPG图片
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/sem.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <semaphore.h>

#include "tslib.h"
#include "head4animation.h"

enum motion{left, right, up, down};

struct tsdev *init_ts(void)
{
	char *tsdevice = getenv("TSLIB_TSDEVICE");
	struct tsdev *ts = ts_open(tsdevice, 0);
	ts_config(ts);

	return ts;
}

int init_fb(void)
{
	char *fbdevice = getenv("TSLIB_FBDEVICE");

	int fd = open(fbdevice, O_RDWR);
	if(fd == -1)
	{
		perror("open()");
	}

	return fd;
}

// 将图片filename里面的信息读出，存放到buf中
void get_image(const char *filename,
			unsigned long (*buf)[WIDTH])
{
	// 打开图片文件，直接读即可，因为读的是bin格式的纯像素RGB信息
	int fd = open(filename, O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		exit(1);
	}

	int n, offset = 0;
	while(1)
	{
		n = read(fd, buf, WIDTH * HEIGHT * 4);
		if(n <= 0)
			break;
		offset += n;
	}
}

// 将纯图片像素信息image直接刷到lcd的framebuffer上
void write_lcd(int lcd, unsigned long (*image)[WIDTH])
{
	// 创建一块framebuffer：FB
	unsigned long (*FB)[WIDTH] = mmap(NULL, SCREEN_SIZE*4,
					PROT_READ | PROT_WRITE,
					MAP_SHARED, lcd, 0);

	// 刷过去！
	memcpy(FB, image, SCREEN_SIZE * 4);
}


void *harvest(void *arg)
{
	struct node
	{
		int *coordinate;
		struct tsdev *TS;
		sem_t *s1;
		sem_t *s2;
	};
	struct node args = *((struct node *)arg);
	struct ts_sample samp;

	int flag = 1;
	while(1)
	{
		// 使用ts_read()来持续地获取触摸屏的坐标值和压力值
		ts_read(args.TS, &samp, 1);

		// 如果坐标值不合法，则丢弃
		if(samp.x <= 0 || samp.x >= 800 ||
		   samp.y <= 0 || samp.y >= 480)
			continue;

		// 坐标值合法，就填入coordinate中
		(args.coordinate)[0] = samp.x;
		(args.coordinate)[1] = samp.y;
		(args.coordinate)[2] = samp.pressure;

		// 获取完完整的坐标值之后，通过s1通知get_motion线程
		sem_post(args.s1);

		// 以下if语句的作用是：首个坐标需要等到get_motion线程读完
		// 后续坐标不需要等待，直接循环覆盖
		if(flag == 1)
		{
			sem_wait(args.s2);
			flag = 0;
		}
	}
}

enum motion get_motion(struct tsdev *TS)
{
	int *coordinate = calloc(sizeof(int), 3);

	// 关键字volatile用来告诉系统，它所修饰的变量是易变的，不能优化
	volatile int *x = &coordinate[0];
	volatile int *y = &coordinate[1];
	volatile int *p = &coordinate[2];

	sem_t s1, s2;
	sem_init(&s1, 0, 0);
	sem_init(&s2, 0, 0);

	// 将坐标值和压力值和信号量打个包，作为参数传递给harvest线程
	struct
	{
		volatile int *coordinate;
		volatile struct tsdev *TS;
		sem_t *s1;
		sem_t *s2;
	}arg={coordinate, TS, &s1, &s2};
	pthread_t tid;
	pthread_create(&tid, NULL, harvest, (void *)&arg);

	// s1用来保证harvest写好数据之后，我才读取起始坐标
	// s2用来保证我读完之后，harvest才写下一个坐标
	sem_wait(arg.s1);
	volatile int x1 = *x, x2=0;
	volatile int y1 = *y, y2=0;
	sem_post(arg.s2);

	while(1)
	{
		if(*p == 0)
		{
			usleep(200000); // 0.2s

			// 如果0.2s内触摸屏的压力值都为0，那么可以断定手指已经离开
			if(*p == 0)
			{
				// 获取终止坐标值，并取消掉harvest线程，退出循环
				x2 = *x;
				y2 = *y;
				if(pthread_cancel(tid) != 0)
					printf("cacel() error");
				break;
			}
		}
	}

	// 以下代码用两个坐标值判断用户的动作
	int delta_x = x1-x2 > 0 ? x1-x2 : x2-x1;
	int delta_y = y1-y2 > 0 ? y1-y2 : y2-y1;

	#ifdef DEBUG
	printf("x1:%u\ty1:%u\n", x1, y1);
	printf("x2:%u\ty2:%u\n", x2, y2);
	printf("dx:%u\tdy:%u\n", delta_x, delta_y);
	#endif

	if(x1 == 0 || x2 == 0)
		return -1;

	if(x1>x2 && delta_x > delta_y)
		return left;
	else if(x2>x1 && delta_x > delta_y)
		return right;
	else if(y1>y2 && delta_y > delta_x)
		return up;
	else if(y2>y1 && delta_y > delta_x)
		return down;
	else
		return -1;
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <some dir includes *.bin>\n", argv[0]);
		exit(1);
	}

	// 初始化触摸屏和LCD显示器
	struct tsdev *TS = init_ts();
	int fd = init_fb();

	// 打开指定目录，并进入该目录
	DIR *dp = opendir(argv[1]);
	if(dp == NULL)
	{
		perror("opendir()");
		exit(1);
	}
	chdir(argv[1]);

	// 定义一个跟LCD尺寸一致的内存缓冲区，作为framebuffer
	unsigned long (*buf)[WIDTH] = calloc(WIDTH * HEIGHT, 4);
	
	int i, n;
	struct dirent *ep;

	// 计算图片数目
	// n包括本目录.和上一级目录..
	for(n=0; (ep=readdir(dp)) && ep!=NULL; n++);

	// 将所有的图片名字存放在filename[]里面
	char *filename[n-2];

	// 重置目录指针，从头又读一遍目录项
	rewinddir(dp);
	for(i=0; i<n-2;)
	{
		ep = readdir(dp);
		if(ep->d_name[0] == '.') // 将以.开头的隐藏文件忽略
		{
			continue;
		}
		filename[i++] = ep->d_name;
	}

	// 再次重置目录指针，显示第一张图片
	// 1: 将图片filename[0]的图像信息读出，放到buf中
	// 2: 将buf设置为LCD的framebuffer
	rewinddir(dp);
	get_image(filename[i=0], buf);
	write_lcd(fd, buf);

	while(1)
	{
		// 分析用户动作
		enum motion m = get_motion(TS);

		// 调试信息
		#ifdef DEBUG
		switch(m)
		{
		case left: printf("left\n" );break;
		case right:printf("right\n");break;
		case up:   printf("up\n"   );break;
		case down: printf("down\n" );break;
		}
		#endif

		// 根据用户动作，显示图片
		#if 1
		switch(m)
		{
		case left:
			if(i >= n-2-1)
				break;
			right2left_out(fd, buf);
			get_image(filename[++i], buf);
			right2left_in(fd, buf);
			break;
		case right:
			if(i <= 0)
				break;
			left2right_out(fd, buf);
			get_image(filename[--i], buf);
			left2right_in(fd, buf);
			break;
		case down:
			blind_window_out(fd, buf);
			blind_window_in(fd, buf);
		case up:
		default:
			/* UNDEFINED */;
		}
		#endif
	}

	return 0;
}
