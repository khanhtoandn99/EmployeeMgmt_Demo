#ifndef MQHANDLER_H
#define MQHANDLER_H

#include <iostream>
#include "common_ipc.h"
// IPC
#include <sys/ipc.h>
#include <sys/msg.h>

using namespace std;

class MqHandler
{
public:
    MqHandler(const char *mqAppServicePath, const int &mqAppServiceKey);
    static MqHandler* getInstance(const char *mqAppServicePath, const int &mqAppServiceKey);

    void send(const int &msgKeyId, const MQ_MSG_DATA_T &msgData);
    ssize_t received(MQ_MSG_DATA_T &msgData);
    void clearMsg();
    int getMsgId();

private:
    key_t m_mqKey;
    int m_mqMsgid;
};
#endif // MQHANDLER_H
