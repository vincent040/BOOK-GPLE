//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/msg/Rose.c
//
//  Author: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  Date: 2016-3
//  
//  Description: 使用消息队列，实现两个进程间通信
//
//  GitHub: github.com/vincent040   Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////////////////

#include <signal.h>
#include "head4msg.h"

int main(int argc, char **argv)
{
	key_t key = ftok(PROJ_PATH, PROJ_ID);
	int msgid = msgget(key, IPC_CREAT | 0666);

	struct msgbuf buf;
	bzero(&buf, sizeof(buf));

	if(msgrcv(msgid, &buf, MSGSIZE, J2R, 0) == -1)
	{
		perror("msgrcv() error");
		exit(1);
	}
	printf("from msg: %s", buf.mtext);

	msgctl(msgid, IPC_RMID, NULL);
	return 0;
}
