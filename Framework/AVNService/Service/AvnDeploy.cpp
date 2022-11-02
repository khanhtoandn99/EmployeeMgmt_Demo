#include "AvnDeploy.h"

AvnDeploy::AvnDeploy()
{
    cout << "[AvnDeploy] " << __func__ << endl;
    m_mqHandler = MqHandler::getInstance(MQ_FTOK_KEY_SERVICE_FILEPATH, MQ_FTOK_KEY_SERVICE_ID);
    if (m_mqHandler == nullptr) {
        cout << "[AvnDeploy] " << __func__ << ", m_mqHandler == nullptr" << endl;
    }
    init();
}

AvnDeploy* g_AvnDeploy = nullptr;
AvnDeploy* AvnDeploy::getInstance()
{
    if(g_AvnDeploy != nullptr)
    {
        return g_AvnDeploy;
    }

    g_AvnDeploy = new AvnDeploy();

    return g_AvnDeploy;
}

void AvnDeploy::init()
{
    cout << "[AvnDeploy] " << __func__ << endl;
    clientMsgKey[0].key = ftok(MQ_FTOK_KEY_APPA_FILEPATH, MQ_FTOK_KEY_APPA_ID);
    clientMsgKey[0].keyId = msgget(clientMsgKey[0].key, 0666 | IPC_CREAT);
    cout << "[AvnDeploy] " << __func__ <<" << Get clientMsgKey[0].keyId = " << clientMsgKey[0].keyId << endl;

    clientMsgKey[1].key = ftok(MQ_FTOK_KEY_APPC_FILEPATH, MQ_FTOK_KEY_APPC_ID);
    clientMsgKey[1].keyId = msgget(clientMsgKey[1].key, 0666 | IPC_CREAT);
    cout << "[AvnDeploy] " << __func__ <<" << Get clientMsgKey[1].keyId = " << clientMsgKey[1].keyId << endl;
}

void AvnDeploy::onResponseScoreData(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
{
    cout << "[AvnDeploy] " << __func__
         << ">> eResult: " << eResult
         << " asmScore: " << asmScore
         << " cppScore: " << cppScore
         << " jsScore: " << jsScore
         << " qmlScore: " << qmlScore
         << " openglScore: " << openglScore
         << endl;
    string msg_text = "";
    msg_text += MQ_CLIENTPATH_AVNSERVICE;
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
    mqrequestGetScoreDataMsg.msg_type = (long)E_MQ_MSG_TYPE_FOR_APP_C;
    // Broadcast to all client
    for (int i = 0; i < MQ_APP_SERVICE_NUM-1; ++i) {
        m_mqHandler->send(clientMsgKey[i].keyId, mqrequestGetScoreDataMsg);
    }
}
