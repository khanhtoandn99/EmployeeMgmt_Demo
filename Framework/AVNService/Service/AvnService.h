#ifndef AVNSERVICE_H
#define AVNSERVICE_H

#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <thread>
#include "common.h"
#include "common_ipc.h"
#include "Mq/MqHandler.h"
#include "Service/AvnDeploy.h"

using namespace std;

class AvnService
{
public:
    AvnService();
    ~AvnService();

    void start();
    void requestGetScoreData(const int &id, const string &name);
    thread runMqReceiveLooper();

private:
    void init();
    void loadEmpData();
    void debugShm(EMPLOYEE_DATA_T *aEmpDataTmp);


    MqHandler *m_mqHandler;
    AvnDeploy *m_deploy;
};

#endif // AVNSERVICE_H
