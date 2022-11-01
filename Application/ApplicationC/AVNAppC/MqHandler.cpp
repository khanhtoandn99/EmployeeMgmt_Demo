#include "MqHandler.h"

MqHandler::MqHandler()
{
    m_mqKey = ftok("progfile", 65);
    m_mqMsgid = msgget(m_mqKey, 0666 | IPC_CREAT);
}

void MqHandler::send(const MQ_MSG_DATA_T &msgData)
{
    qDebug() << __func__ << ">> msgData.msg_type: " << msgData.msg_type << "msgData.msg_text: " << msgData.msg_text;
    MQ_MSG_DATA_T _msgData = msgData;
    msgsnd(m_mqMsgid, &_msgData, sizeof(msgData), 0);
}


ssize_t MqHandler::received(MQ_MSG_DATA_T &msgData)
{
    ssize_t ssize = msgrcv(m_mqMsgid, &msgData, sizeof(msgData),1,0);
    return ssize;
}
