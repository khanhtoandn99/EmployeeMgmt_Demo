#include "MqHandler.h"

MqHandler::MqHandler(const char *mqAppServicePath, const int &mqAppServiceKey)
{
    cout << "[MqHandler] " << __func__ << endl;
    m_mqKey = ftok(mqAppServicePath, mqAppServiceKey);
    m_mqMsgid = msgget(m_mqKey, 0666 | IPC_CREAT);
    cout << "[MqHandler] " << __func__ << " Generated m_mqMsgid = " << m_mqMsgid << endl;
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
    cout << "[MqHandler] " << __func__ << " msgKeyId: " << msgKeyId << ", msgData.msg_type: " << msgData.msg_type << ", msgData.msg_text: " << msgData.msg_text << endl;
    msgsnd(msgKeyId, &msgData, sizeof(msgData), 0);
}

ssize_t MqHandler::received(MQ_MSG_DATA_T &msgData)
{
    ssize_t ssize = msgrcv(m_mqMsgid, &msgData, sizeof(msgData), msgData.msg_type, 0);
    return ssize;
}

void MqHandler::clearMsg()
{
    cout << "[MqHandler] " << __func__ << endl;
//     to destroy the message queue
    msgctl(m_mqMsgid, IPC_RMID, NULL);
}

int MqHandler::getMsgId()
{
    cout << "[MqHandler] " << __func__ << endl;
    return m_mqMsgid;
}
