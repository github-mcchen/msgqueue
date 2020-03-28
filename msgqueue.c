#include "msgqueue.h"


/**
 * @brief 创建一个消息队列
 * @param name 消息队列名称
 * @return 返回一个消息队列标识符MESSAGEQ_ID
 */
MESSAGEQ_ID create_msgqueue(char * name)
{
    char syscmd[32] = {0x00};
    char filename[32] = {0x00};

    snprintf(filename, sizeof(filename), "/tmp/%s.msgq", name);

    snprintf(syscmd, sizeof(syscmd), "rm -f %s", filename);
    system(syscmd);

    snprintf(syscmd, sizeof(syscmd), "touch %s", filename);
    system(syscmd);

    key_t key = ftok(filename, 0x01);

    MESSAGEQ_ID id = msgget(key,IPC_CREAT | 0755);

    return id;
}

/**
 * @brief 推送一条消息到消息队列
 * @param msgqid, 消息队列标识
 * @param msg, 推送的消息指针
 * @param msglen, 推送消息长度
 * @return bool, success or not
 */
bool msgqueue_post(MESSAGEQ_ID msgqid, uint8_t * msg, uint8_t msglen)
{
     MsgQueue_t Msgs =
    {
        .msgtype = 1,
        .msgbuff = {0},
    };

    if(msg == NULL || msglen == 0 || msglen > sizeof(Msgs.msgbuff))
        return false;

    memcpy(Msgs.msgbuff, msg, msglen);
    msgsnd(msgqid, &Msgs, sizeof(Msgs.msgbuff), 0);

    return true;
}

/**
 * @brief 获取消息
 * @param msgqid, 消息队列标识
 * @param msg, 获取的消息存储缓冲区指针
 * @param msglen, 能够存的最大消息长度
 * @return bool, success or not
 */
bool msgqueue_wait(MESSAGEQ_ID msgqid, uint8_t * msg, uint8_t msglen)
{
    MsgQueue_t Msgs;

    if(msg == NULL || msglen == 0 || msglen > sizeof(Msgs.msgbuff))
        return false;

    msgrcv(msgqid, &Msgs, sizeof(Msgs.msgbuff), 0, 0);

    memcpy(msg, Msgs.msgbuff, msglen);

    return true;
}

/**
 * @brief 获取消息队列中的缓冲的消息数量
 * @param msgqid, 消息队列标识
 * @return uint32_t, the result
 */
uint32_t msgqueue_getSize(MESSAGEQ_ID msgqid)
{
    struct msqid_ds buffer;

    msgctl(msgqid, IPC_STAT, &buffer);

    return buffer.msg_qnum;
}

/**
 * @brief 删除消息队列
 * @param msgqid消息队列标识
 */
void msgqueue_delete(MESSAGEQ_ID msgqid)
{
    msgctl(msgqid, IPC_RMID, NULL);
}


