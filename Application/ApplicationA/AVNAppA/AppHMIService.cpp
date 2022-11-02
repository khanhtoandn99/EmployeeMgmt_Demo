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
            char clientPath[100];
            sscanf(mqMsgBuffer.msg_text, "%s", clientPath);
            qDebug("[%s] %s << clientPath: %s", __FILE__, __func__, clientPath);
            qDebug("[%s] %s << msg_type: %d", __FILE__, __func__, (int)mqMsgBuffer.msg_type);
            E_GET_SCORE_DATA_RESULT eResult;
            int asmScore, cppScore, jsScore, qmlScore, openglScore;
            sscanf(mqMsgBuffer.msg_text, "%s %d %d %d %d %d %d"
                    ,clientPath
                    ,&eResult
                    ,&asmScore
                    ,&cppScore
                    ,&jsScore
                    ,&qmlScore
                    ,&openglScore);
            onResponseScoreData(eResult, asmScore, cppScore, jsScore, qmlScore, openglScore);
            memset(&mqMsgBuffer, 0x0, sizeof(MQ_MSG_DATA_T));
        }
    }
}

void AppHMIService::requestGetScoreData(const int &id, const QString &name)
{
    qDebug("[%s] %s >> id: %d, name: %s", __FILE__, __func__, id, name.toStdString().c_str());
    QString msg_text = MQ_CLIENTPATH_AVNAPPC;
    msg_text += " ";
    msg_text += QString::number(id);
    msg_text += " ";
    msg_text += name;

    MQ_MSG_DATA_T mqrequestGetScoreDataMsg;
    memcpy(mqrequestGetScoreDataMsg.msg_text, msg_text.toStdString().c_str(), sizeof(char)*MQ_MSG_DATA_MAX);
    mqrequestGetScoreDataMsg.msg_type = (long)E_MQ_MSG_TYPE_FOR_SERVICE;
    key_t keyTmp = ftok(MQ_FTOK_KEY_SERVICE_FILEPATH, MQ_FTOK_KEY_SERVICE_ID);
    m_mqHandler->send(msgget(keyTmp, 0666 | IPC_CREAT), mqrequestGetScoreDataMsg);
}

void AppHMIService::onResponseScoreData(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
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

    qDebug("[%s] %s << emit signalUpdateScoreModel", __FILE__, __func__);
    emit signalUpdateScoreModel(asmScore, cppScore, jsScore, qmlScore, openglScore);

}
