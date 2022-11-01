#include "AppHMIService.h"

AppHMIService::AppHMIService(QObject *parent)
    : QObject{parent}
{
    m_mqHandler = new MqHandler();
}


void AppHMIService::getEmpDetailData(const QString &name)
{
    qDebug() << __func__ << ">> name: " << name;
    QString sMsgContent = __func__;
    sMsgContent += " ";
    sMsgContent += name;

    MQ_MSG_DATA_T mqGetEmpDetailDataMsg;
    memcpy(mqGetEmpDetailDataMsg.msg_text, sMsgContent.toStdString().c_str(), sizeof(mqGetEmpDetailDataMsg));
    mqGetEmpDetailDataMsg.msg_type = E_MQ_MSG_TYPE_GET;
    m_mqHandler->send(mqGetEmpDetailDataMsg);
}
