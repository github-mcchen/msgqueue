#ifndef __MSGQUEUE_H__
#define __MSGQUEUE_H__
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uint8_t         unsigned char
#define uint32_t        unsigned int

typedef int MESSAGEQ_ID;

typedef struct
{
    long msgtype;
    char msgbuff[64];
}MsgQueue_t;

MESSAGEQ_ID create_msgqueue(char * name);
bool msgqueue_post(MESSAGEQ_ID msgqid, uint8_t * msg, uint8_t msglen);
bool msgqueue_wait(MESSAGEQ_ID msgqid, uint8_t * msg, uint8_t msglen);
uint32_t msgqueue_getSize(MESSAGEQ_ID msgqid);
void msgqueue_delete(MESSAGEQ_ID msgqid);


#endif
