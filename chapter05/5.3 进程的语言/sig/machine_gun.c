//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/sig/machine_gun.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 本程序向指定进程发送除SIGKILL和SIGSTOP之外的所有
//               信号
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <target-PID>\n", argv[0]);
	}
	int i;
	for(i=SIGHUP; i<=SIGRTMAX; i++)
	{
		if(i == SIGKILL || i == SIGSTOP ||
		   i == 32      || i == 33)
			continue;

		kill(atoi(argv[1]), i);
	}

	return 0;
}
