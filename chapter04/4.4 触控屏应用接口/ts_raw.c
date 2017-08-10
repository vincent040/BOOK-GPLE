//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.4/ts_raw.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了使用函数read()直接读取触摸屏数据的例子
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/input.h>

int main(int argc, char **argv)
{
	int ts = open("/dev/event0", O_RDONLY);

	struct input_event buf;
	bzero(&buf, sizeof(buf));

	while(1)
	{
		read(ts, &buf, sizeof(buf));

		switch(buf.type)
		{
		case EV_SYN:
			printf("----------------------- SYN --------------------\n");
			break;
		case EV_ABS:
			printf("time: %u.%u\ttype: EV_ABS\t",
				buf.time.tv_sec, buf.time.tv_usec);
			switch(buf.code)
			{
			case ABS_X:
				printf("X:%u\n", buf.value);
				break;
			case ABS_Y:
				printf("Y:%u\n", buf.value);
				break;
			case ABS_PRESSURE:
				printf("pressure:%u\n", buf.value);
			}
		}
	}
	return 0;
}
