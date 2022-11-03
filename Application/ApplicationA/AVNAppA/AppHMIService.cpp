#include "AppHMIService.h"

AppHMIService::AppHMIService(QObject *parent)
    : QThread{parent}
{
    qDebug("[%s] %s", __FILE__, __func__);
    m_mqHandler = MqHandler::getInstance(MQ_FTOK_KEY_APPA_FILEPATH, MQ_FTOK_KEY_APPA_ID);
}

void AppHMIService::run()
{
    qDebug("[%s] %s", __FILE__, __func__);
    runMqReceiveLooper();
}

void AppHMIService::runMqReceiveLooper()
{
    qDebug("[%s] %s", __FILE__, __func__);

    MQ_MSG_DATA_T mqMsgBuffer;
    memset(mqMsgBuffer.msg_text, 0x0, sizeof(mqMsgBuffer.msg_text));
    mqMsgBuffer.msg_type = E_MQ_MSG_TYPE_FOR_APP_A;
    qDebug("[%s] %s with msgId = %d", __FILE__, __func__, m_mqHandler->getMsgId());
    while (1)
    {
        if (m_mqHandler->received(mqMsgBuffer) > 0)
        {
            E_MQ_MSG_APP_SERVICE_ID eClientID;
            int funcId;
            sscanf(mqMsgBuffer.msg_text, "%d %d", &eClientID, &funcId);
            qDebug() << "[AvnService] "<<__func__ << "eClientID: "<<eClientID;
            qDebug() << "[AvnService] "<<__func__ << "funcId: "<<funcId;

            if (eClientID == E_MQ_MSG_SERVICE_B_ID) {
                switch (funcId) {
                case E_MQ_MSG_SERVICE_FUNC_ID_onResponseScoreDataToA:
                {
                    E_GET_SCORE_DATA_RESULT eResult;
                    int asmScore, cppScore, jsScore, qmlScore, openglScore;
                    sscanf(mqMsgBuffer.msg_text, "%d %d %d %d %d %d %d %d", &eClientID, &funcId, &eResult, &asmScore, &cppScore, &jsScore, &qmlScore, &openglScore);
                    onResponseScoreDataToA(eResult, asmScore, cppScore, jsScore, qmlScore, openglScore);
                }
                    break;
                case E_MQ_MSG_SERVICE_FUNC_ID_onNotifyDataChanged:
                {
                    onNotifyDataChanged();
                }
                    break;
                default:
                    break;
                }
            }
            else {
                qDebug("[%s] %s << Unknow Client ID", __FILE__, __func__);
            }
        }
    }
}

void AppHMIService::requestGetScoreDataFromA(const int &id, const QString &name)
{
    qDebug("[%s] %s >> id: %d, name: %s", __FILE__, __func__, id, name.toStdString().c_str());
    MQ_MSG_DATA_T mqrequestGetScoreDataMsg;
    QString msg_text = "";
    msg_text += QString::number(E_MQ_MSG_APPLICATION_A_ID);
    msg_text += " ";
    msg_text += QString::number(E_MQ_MSG_SERVICE_FUNC_ID_requestGetScoreDataFromA);
    msg_text += " ";
    msg_text += QString::number(id);
    msg_text += " ";
    msg_text += name;

    memcpy(mqrequestGetScoreDataMsg.msg_text, msg_text.toStdString().c_str(), sizeof(char)*MQ_MSG_DATA_MAX);
    mqrequestGetScoreDataMsg.msg_type = (long)E_MQ_MSG_TYPE_FOR_SERVICE;
    key_t keyTmp = ftok(MQ_FTOK_KEY_SERVICE_FILEPATH, MQ_FTOK_KEY_SERVICE_ID);
    m_mqHandler->send(msgget(keyTmp, 0666 | IPC_CREAT), mqrequestGetScoreDataMsg);
}

void AppHMIService::onResponseScoreDataToA(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
{
    qDebug("[%s] %s >> eResult: %d, asmScore: %d, cppScore: %d, jsScore: %d, qmlScore: %d, openglScore: %d"
           ,__FILE__
           ,__func__
           ,eResult
           ,asmScore
           ,cppScore
           ,jsScore
           ,qmlScore
           ,openglScore);
    if (eResult != E_GET_SCORE_DATA_RESULLT_OK) return;

    qDebug("[%s] %s << emit signalResponseScoreDataToA", __FILE__, __func__);
    emit signalResponseScoreDataToA(asmScore, cppScore, jsScore, qmlScore, openglScore);

}

void AppHMIService::onNotifyDataChanged()
{
    qDebug("[%s] %s", __FILE__, __func__);
    qDebug("[%s] %s << emit signalNotifyDataChanged", __FILE__, __func__);
    emit signalNotifyDataChanged();
}
