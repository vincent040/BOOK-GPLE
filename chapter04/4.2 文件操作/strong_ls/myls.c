//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/strong_ls/myls.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: strong_ls基本功能函数列表
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include "myls.h"

void err_sys(const char *info)
{
	perror(info);
	exit(1);
}

void err_quit(const char *info)
{
	fprintf(stderr, "%s", info);
	exit(2);
}

int Stat(const char *path, struct stat *buf)
{
	int ret;
	ret = stat(path, buf);

	if(ret < 0)
		err_sys("stat error");

	return ret;
}

DIR *Opendir(const char *name)
{
	DIR *dp;
	dp = opendir(name);

	if(dp == NULL)
		err_sys("opendir error");

	return dp;
}

int Closedir(DIR *dirp)
{
	int ret;
	ret = closedir(dirp);

	if(ret < 0)
		err_sys("closedir error");

	return ret;
}

char *mode(struct stat *ps)
{
	static char mode[10];

	switch(ps->st_mode & S_IFMT)
	{
		case S_IFSOCK: mode[0] = 's';break;
		case S_IFLNK: mode[0] = 'l';break;
		case S_IFDIR: mode[0] = 'd';break;
		case S_IFREG: mode[0] = '-';break;
		case S_IFBLK: mode[0] = 'b';break;
		case S_IFCHR: mode[0] = 'c';break;
		case S_IFIFO: mode[0] = 'p';
	}
	
	char rwx[] = {'r', 'w', 'x'};
	int i;
	for(i=0; i<9; i++)
		snprintf(mode+i+1, 10, "%c",
				(ps->st_mode&(0400>>i))?rwx[i%3]:'-');

	return mode;
}

int hln(struct stat *ps)
{
	return ps->st_nlink;
}

char *user(struct stat *ps)
{
	struct passwd *pw;
	pw = getpwuid(ps->st_uid);

	return pw->pw_name;
}

char *group(struct stat *ps)
{
	struct group *gr;
	gr = getgrgid(ps->st_gid);

	return gr->gr_name;
}

char *size_dev(struct stat *ps)
{
	static char size_or_dev[10];

	if(((ps->st_mode&S_IFMT) == S_IFBLK) ||
		((ps->st_mode&S_IFMT) == S_IFCHR))
		snprintf(size_or_dev, 10,
			"%d,%4d", major(ps->st_rdev), minor(ps->st_rdev));
	else
		snprintf(size_or_dev, 10, "%d", (int)ps->st_size);

	return size_or_dev;
}

char *mtime(struct stat *ps)
{
	char *t;
	t = ctime(&ps->st_mtime);
	return t;
}

void print_color_name(struct stat *ps, char *path)
{
	if((ps->st_mode&S_IFMT) == S_IFDIR)
		blue(path);
	else if((ps->st_mode&S_IFMT) == S_IFLNK)
		cyan(path);
	else if((ps->st_mode & S_IXUSR ||
		 ps->st_mode & S_IXGRP ||
		 ps->st_mode & S_IXOTH))
		green(path);
	else
		other(path);
}
