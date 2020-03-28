#include "msgqueue.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>


static MESSAGEQ_ID msgQ;
typedef struct
{
    char *msg;
}Msg_t;

/**
 * @brief message_run
 */
void message_run(void)
{
    Msg_t msgR;
    Msg_t msgS;

    msgS.msg = "hello world";

    msgQ = create_msgqueue("Msg");
    //分发消息,接收消息
    while(1)
    {
        //推送消息
        printf("send message\n");
        msgqueue_post(msgQ, (uint8_t*)&msgS, sizeof(msgS));

        //接收消息
        if(msgqueue_wait(msgQ, (uint8_t*)&msgR, sizeof(msgR)) == false)
            continue;

        //打印消息
        printf("get message: %s\n", msgR.msg);
        sleep(1);
    }
}

int main(void)
{
    message_run();
    return 0;
}
