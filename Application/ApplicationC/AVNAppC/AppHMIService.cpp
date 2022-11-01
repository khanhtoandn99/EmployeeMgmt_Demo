#include "AppHMIService.h"

AppHMIService::AppHMIService(QObject *parent)
    : QObject{parent}
{
    m_mqHandler = new MqHandler();
//    run();
}

void AppHMIService::run()
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, (void*)runMqReceiveLooper, NULL);
    pthread_join(ptid, NULL);
//    runMqReceiveLooper();
}

void AppHMIService::runMqReceiveLooper()
{
    qDebug() << __func__;

    MQ_MSG_DATA_T mqMsgBuffer;
    while (1)
    {
        if (m_mqHandler->received(mqMsgBuffer) > 0)
        {
            char clientPath[100];
            sscanf(mqMsgBuffer.msg_text, "%s", clientPath);
            qDebug() << "clientPath = " << clientPath;
            qDebug() << "msg_type = " << mqMsgBuffer.msg_type;
            if (strncmp(clientPath, MQ_CLIENTPATH_AVNSERVICE, MQ_MSG_DATA_MAX-1) == 0) {
                switch (mqMsgBuffer.msg_type) {
                case E_MQ_MSG_TYPE_ONRESPONSESCOREDATA:
                {
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
                }
                    break;
                default:
                    qDebug() << "Unknown mqMsgBuffer.msg_type";
                    break;
                }
            }
            else {
                qDebug() << "Unknow client requested";
            }
            memset(&mqMsgBuffer, 0x0, sizeof(MQ_MSG_DATA_T));
        }
    }
    pthread_exit(NULL);
}

void AppHMIService::requestGetScoreData(const int &id, const QString &name)
{
    qDebug() << __func__ << ">> name: " << name;
    QString msg_text = MQ_CLIENTPATH_AVNAPPC;
    msg_text += " ";
    msg_text += QString::number(id);
    msg_text += " ";
    msg_text += name;

    MQ_MSG_DATA_T mqrequestGetScoreDataMsg;
    memcpy(mqrequestGetScoreDataMsg.msg_text, msg_text.toStdString().c_str(), sizeof(char)*MQ_MSG_DATA_MAX);
    mqrequestGetScoreDataMsg.msg_type = E_MQ_MSG_TYPE_REQUESTGETSCOREDATA;
    m_mqHandler->send(mqrequestGetScoreDataMsg);
}

void AppHMIService::onResponseScoreData(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
{
    qDebug("AppHMIService::%s >> eResult: %d, asmScore: %d, cppScore: %d, jsScore: %d, qmlScore: %d, openglScore: %d"
           ,eResult
           ,asmScore
           ,cppScore
           ,jsScore
           ,qmlScore
           ,openglScore);
    if (eResult != E_GET_SCORE_DATA_RESULLT_OK) return;

    emit signalUpdateScoreModel(asmScore, cppScore, jsScore, qmlScore, openglScore);

}
