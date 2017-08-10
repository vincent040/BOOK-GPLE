//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.2/wait.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 演示了函数wait()的基本用法和特点
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

int main(int argc, char **argv)
{
	pid_t x = fork();

	if(x == 0)
	{
		execl("./child_elf", "child_elf", NULL);
	}
	
	if(x > 0)
	{
		int status;
		wait(&status);

		if(WIFEXITED(status))
		{
			printf("child exit normally, "
			       "exit value: %hhu\n", WEXITSTATUS(status));
		}
		
		if(WIFSIGNALED(status))
		{
			printf("child killed by signal: %u\n",
				WTERMSIG(status));
		}
	}

	return 0;
}
