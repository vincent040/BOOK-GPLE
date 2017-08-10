//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/strong_ls/main.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用stat()来实现命令 ls -l 的功能：
//               1，显示文件的类型、权限、所有者、名字等基本信息
//               2，不同类型文件用不同的颜色
//               3，设备文件显示设备号，普通文件显示大小
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "myls.h"

int main(int argc, char **argv)
{
	umask(0);
	struct stat s;
	char *path;

	if(argc == 1)
	{
		path = ".";
		Stat(path, &s);
	}
	else if(argc == 2)
	{
		path = argv[1];
		Stat(path, &s);
	}
	else
		err_quit("too many arguments.\n");


	if((s.st_mode & S_IFMT) == S_IFDIR)
	{
		DIR *dp;
		struct dirent *ep;

		dp = Opendir(path);

		chdir(path);
		while((ep=readdir(dp)) != NULL)
		{
			if(ep->d_name[0] == '.')
				continue;

			lstat(ep->d_name, &s);

			printf("%s%3d %7s %7s%8s %.16s ",
				mode(&s), hln(&s), user(&s), group(&s),
				size_dev(&s), mtime(&s));

			print_color_name(&s, ep->d_name);
		}

		Closedir(dp);
	}

	else
	{
		printf("%s%3d %7s %7s%8s %.16s ", mode(&s), hln(&s),
			user(&s), group(&s), size_dev(&s), mtime(&s));

		print_color_name(&s, path);
	}
		
	exit(0);
}
