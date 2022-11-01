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

    void onResponseScoreData(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

private:
    MqHandler *m_mqHandler;
};

#endif // AVNDEPLOY_H
