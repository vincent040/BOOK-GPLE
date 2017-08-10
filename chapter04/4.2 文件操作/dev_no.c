//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/dev_no.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 利用函数stat()获取文件信息，并判断文件是否是设备节
//               点文件，如果是则打印其设备号。
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		exit(1);
	}


	struct stat info;
	stat(argv[1], &info);


	if(S_ISCHR(info.st_mode) ||
	   S_ISBLK(info.st_mode))
	{
		printf("regular file: %d, %d\n",
			major(info.st_rdev),
			minor(info.st_rdev));
	}


	else
		printf("device: %d, %d\n",
			major(info.st_dev),
			minor(info.st_dev));

	printf("%d\n", info.st_blksize);

	return 0;
}
