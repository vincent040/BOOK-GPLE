//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.3/opendir_readdir.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了目录操作基本API的使用细节
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
#include <dirent.h>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <dir>\n", argv[0]);
		exit(1);
	}

	DIR *dp = opendir(argv[1]);

	struct dirent *ep = NULL;
	while(1)
	{
		ep = readdir(dp);
		if(ep == NULL)
			break;

		printf("%s\n", ep->d_name);
	}
	

	return 0;
}
