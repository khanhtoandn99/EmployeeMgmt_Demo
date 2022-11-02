#include "MqHandler.h"

MqHandler::MqHandler(const char *mqAppServicePath, const int &mqAppServiceKey)
{
    qDebug("[%s] %s\n", __FILE__, __func__);
    m_mqKey = ftok(mqAppServicePath, mqAppServiceKey);
    m_mqMsgid = msgget(m_mqKey, 0666 | IPC_CREAT);
    qDebug("[%s] %s << Generated m_mqMsgid: %d\n", __FILE__, __func__, m_mqMsgid);
}

MqHandler* g_MqHandler = nullptr;
MqHandler* MqHandler::getInstance(const char *mqAppServicePath, const int &mqAppServiceKey)
{
    if(g_MqHandler != nullptr)
    {
        return g_MqHandler;
    }

    g_MqHandler = new MqHandler(mqAppServicePath, mqAppServiceKey);

    return g_MqHandler;
}

void MqHandler::send(const int &msgKeyId, const MQ_MSG_DATA_T &msgData)
{
    qDebug("[%s] %s >> msgKeyId: %d, msgData.msg_type: %d, msgData.msg_text: %s\n", __FILE__, __func__, msgKeyId, (int)msgData.msg_type, msgData.msg_text);
    msgsnd(msgKeyId, &msgData, sizeof(msgData), 0);
}

ssize_t MqHandler::received(MQ_MSG_DATA_T &msgData)
{
//    qDebug("[%s] %s << Current m_mqMsgid handling: %d\n", __FILE__, __func__, m_mqMsgid);
    ssize_t ssize = msgrcv(m_mqMsgid, &msgData, sizeof(msgData), msgData.msg_type, 0);
    return ssize;
}

void MqHandler::clearMsg()
{
    qDebug("[%s] %s\n", __FILE__, __func__);
//     to destroy the message queue
    msgctl(m_mqMsgid, IPC_RMID, NULL);
}

int MqHandler::getMsgId()
{
    qDebug("[%s] %s\n", __FILE__, __func__);
    return m_mqMsgid;
}
