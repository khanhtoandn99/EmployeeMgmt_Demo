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
#include "common.h"
#include "common_ipc.h"
#include "Mq/MqHandler.h"

using namespace std;

class AvnService
{
public:
    AvnService();
    virtual ~AvnService();

    void start();

private:
    void init();
    void loadEmpData();
    void debugShm(EMPLOYEE_DATA_T *aEmpDataTmp);
    void runMqReceiveLooper();

    MqHandler m_mqHandler;
};

#endif // AVNSERVICE_H
