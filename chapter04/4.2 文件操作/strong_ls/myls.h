//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch04/4.2/strong_ls/myls.h
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: strong_ls头文件
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#ifndef _MYLS_H_
#define _MYLS_H_

#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <time.h>
#include <dirent.h>

/* printf color */
#define NONE "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

#define HIGHTLIGHT "\033[1m"
#define UNDERLINE  "\033[4m"
#define FLICKER    "\033[5m"
#define INVERSE    "\033[7m"

#define MAX_LINE 255

#define blue(string) \
	do{printf("\033[0;32;34m%-4s\033[m\n", string);}while(0)

#define green(string) \
	do{printf("\033[0;32;32m%-4s\033[m\n", string);}while(0)

#define cyan(string) \
	do{ \
		char s[MAX_LINE]; \
		readlink(string, s, MAX_LINE); \
		printf("\033[0;36m%-4s\033[m -> %s\n", string, s); \
	}while(0)

#define other(string) \
	 do{printf("%-4s\n", string);}while(0)

void err_sys(const char *);
void err_quit(const char *);
int Stat(const char *, struct stat *);
DIR *Opendir(const char *);
int Closedir(DIR *);

char *mode(struct stat *);
int hln(struct stat *);
char *user(struct stat *);
char *group(struct stat *);
char *size_dev(struct stat *);
char *mtime(struct stat *);
void print_color_name(struct stat *, char *);

#endif
