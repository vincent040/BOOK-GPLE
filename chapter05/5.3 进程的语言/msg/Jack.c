//////////////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2016, GEC Tech. Co., Ltd.
//
//  File name: GPLE/ch05/5.3/msg/Jack.c
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

#include "head4msg.h"

int main(int argc, char **argv)
{
	key_t key = ftok(PROJ_PATH, PROJ_ID);
	int msgid = msgget(key, IPC_CREAT | 0666);

	struct msgbuf message;
	bzero(&message, sizeof(message));

	message.mtype = J2R;
	strncpy(message.mtext, "abcxyz\n", MSGSIZE);

	if(msgsnd(msgid, &message, strlen(message.mtext), 0) != 0)
	{
		perror("msgsnd() error");
		exit(1);
	}

	return 0;
}
