#include "MqHandler.h"

MqHandler::MqHandler()
{
    cout << __func__ << endl;
    m_mqKey = ftok(MQ_KEY_FTOK_FILEPATH, 65);
    m_mqMsgid = msgget(m_mqKey, 0666 | IPC_CREAT);
    cout << __func__ << "<< m_mqMsgid = " << m_mqMsgid << endl;
}

void MqHandler::send(const MQ_MSG_DATA_T &msgData)
{
    cout << "MqHandler::" << __func__ << ">> msgData.msg_type: " << msgData.msg_type << "msgData.msg_text: " << msgData.msg_text << endl;
    MQ_MSG_DATA_T _msgData = msgData;
    msgsnd(m_mqMsgid, &_msgData, sizeof(msgData), 0);
}

ssize_t MqHandler::received(MQ_MSG_DATA_T &msgData)
{
    ssize_t ssize = msgrcv(m_mqMsgid, &msgData, sizeof(MQ_MSG_DATA_T),1,0);
    return ssize;
}
