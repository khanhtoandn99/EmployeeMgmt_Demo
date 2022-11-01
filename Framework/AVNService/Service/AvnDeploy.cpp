#include "AvnDeploy.h"

AvnDeploy::AvnDeploy()
{
    std::cout << __func__ << std::endl;
    m_mqHandler = new MqHandler;
}

void AvnDeploy::onResponseScoreData(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
{
    printf("AvnDeploy::%s >> asmScore: %d, cppScore: %d, jsScore: %d, qmlScore: %d, openglScore: %d\n", __func__,asmScore,cppScore,jsScore,qmlScore,openglScore);
    string msg_text = MQ_CLIENTPATH_AVNSERVICE;
    msg_text += " ";
    msg_text += to_string((int)eResult);
    msg_text += " ";
    msg_text += to_string(asmScore);
    msg_text += " ";
    msg_text += to_string(cppScore);
    msg_text += " ";
    msg_text += to_string(jsScore);
    msg_text += " ";
    msg_text += to_string(qmlScore);
    msg_text += " ";
    msg_text += to_string(openglScore);

    MQ_MSG_DATA_T mqrequestGetScoreDataMsg;
    memcpy(mqrequestGetScoreDataMsg.msg_text, msg_text.c_str(), sizeof(char)*MQ_MSG_DATA_MAX);
    mqrequestGetScoreDataMsg.msg_type = E_MQ_MSG_TYPE_ONRESPONSESCOREDATA;
    m_mqHandler->send(mqrequestGetScoreDataMsg);
}
