#ifndef AVNDEPLOY_H
#define AVNDEPLOY_H

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <vector>
#include "common.h"
#include "common_ipc.h"
#include "Mq/MqHandler.h"

class AvnDeploy
{
public:
    AvnDeploy();
    ~AvnDeploy();

    static AvnDeploy* getInstance();

    void init();

    // IPC To client App A
    void onResponseScoreDataToA(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

    // IPC To client App C
    void onResponseScoreDataToC(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

private:
    MqHandler *m_mqHandler;
    MQ_MSG_KEY_T clientMsgKey[MQ_APP_SERVICE_NUM-1];
    E_MQ_MSG_TYPE clientMsgType[MQ_APP_SERVICE_NUM-1];
};

#endif // AVNDEPLOY_H
