#ifndef _HEAD4MSG_H_
#define _HEAD4MSG_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGSIZE 7

#define PROJ_PATH "/tmp"
#define PROJ_ID 1

#define J2R 1L
#define R2J 2L

struct msgbuf
{
	long mtype;
	char mtext[MSGSIZE];
};

#endif
