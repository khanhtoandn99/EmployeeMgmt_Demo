#ifndef MQHANDLER_H
#define MQHANDLER_H

#include <iostream>
#include "common_ipc.h"
#include <qdebug.h>
// IPC
#include <sys/ipc.h>
#include <sys/msg.h>

class MqHandler
{
public:
    MqHandler();

    void send(const MQ_MSG_DATA_T &msgData);
    ssize_t received(MQ_MSG_DATA_T &msgData);

private:
    key_t m_mqKey;
    int m_mqMsgid;
};

#endif // MQHANDLER_H
