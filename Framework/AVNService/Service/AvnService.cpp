#include "AvnService.h"
#include <iostream>

AvnService::AvnService()
{
    cout << "[AvnService] %s\n" << __func__ << endl;
    m_mqHandler = MqHandler::getInstance(MQ_FTOK_KEY_SERVICE_FILEPATH, MQ_FTOK_KEY_SERVICE_ID);
    m_deploy = AvnDeploy::getInstance();
//    m_mqHandler = new MqHandler(MQ_FTOK_KEY_SERVICE_FILEPATH, MQ_FTOK_KEY_SERVICE_ID);
//    m_deploy = new AvnDeploy;
    if (m_mqHandler == nullptr) {cout << "[AvnService] %s << m_mqHandler is nullptr\n" << __func__ << endl;}
    if (m_deploy == nullptr) {cout << "[AvnService] %s << m_deploy is nullptr\n" << __func__ << endl;}
    init();
}

AvnService::~AvnService()
{
    cout << "[AvnService] " << __func__ << endl;
}

void AvnService::init()
{
    cout << "[AvnService] " << __func__ << endl;
    loadEmpData();
}

void AvnService::start()
{
    cout << "[AvnService] " << __func__ << endl;
}


void AvnService::loadEmpData()
{
    cout << "[AvnService] " << __func__ << endl;

    // Init Shm
    // Write to Shm:
    key_t key = ftok("shmfile",65);
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096,0666|IPC_CREAT);
    // shmat to attach to shared memory
    EMPLOYEE_DATA_T *pShMem = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);

    // Read data from file and push to Shm
    std::string sLineData;
    EMPLOYEE_DATA_T *pEmpDataTmp = new EMPLOYEE_DATA_T[EMPLOYEE_IN_LIST_MODEL_MAX];

    std::ifstream rfData;
    rfData.open(EMPLOYEE_DATA_MODEL_FILE_PATH, std::ifstream::in);
    if (rfData.is_open()) {
        int i = 0;
        while (std::getline(rfData, sLineData) && i < 10)
        {
            // get element data from file:   id name asmScore cppScore jsScore qmlScore openglScore average isSelected
            sscanf(sLineData.c_str(),       "%d  %s     %d       %d       %d       %d         %d      %8f       %d"
                                            ,&pEmpDataTmp[i].id
                                            , pEmpDataTmp[i].name
                                            ,&pEmpDataTmp[i].asmScore
                                            ,&pEmpDataTmp[i].cppScore
                                            ,&pEmpDataTmp[i].jsScore
                                            ,&pEmpDataTmp[i].qmlScore
                                            ,&pEmpDataTmp[i].openglScore
                                            ,&pEmpDataTmp[i].average
                                            ,&pEmpDataTmp[i].isSelected);
            ++i;
        }
        rfData.close();
    }
    else {
        cout << "[AvnService] " << __func__ << "File: " << EMPLOYEE_DATA_MODEL_FILE_PATH << " open failed!" << endl;
    }

    memcpy(pShMem, pEmpDataTmp, sizeof(EMPLOYEE_DATA_T)*EMPLOYEE_IN_LIST_MODEL_MAX);

//    debugShm(pShMem);
    cout << "[AvnService] "<< __func__ << "Data wrote to Shared Memory" << endl;
    delete[] pEmpDataTmp;
    pEmpDataTmp = nullptr;


    //detach from shared memory
    shmdt(pEmpDataTmp);
}

void AvnService::debugShm(EMPLOYEE_DATA_T *aEmpDataTmp)
{
    cout << "[AvnService] " << __func__ << endl;
    if (aEmpDataTmp == nullptr) {
        cout << "[AvnService] " << __func__ << "nullptr" << endl;
        return;
    }

    for (int i = 0; i < EMPLOYEE_IN_LIST_MODEL_MAX; ++i) {
        cout  << aEmpDataTmp[i].id << " "
                << aEmpDataTmp[i].name << " "
                << aEmpDataTmp[i].asmScore << " "
                << aEmpDataTmp[i].cppScore << " "
                << aEmpDataTmp[i].jsScore << " "
                << aEmpDataTmp[i].qmlScore << " "
                << aEmpDataTmp[i].openglScore << " "
                << aEmpDataTmp[i].average << " "
                << aEmpDataTmp[i].isSelected << endl;
    }
}

void AvnService::requestGetScoreDataFromC(const int &id, const string &name)
{
    cout << "[AvnService] "<<__func__ << "id: "<<id << " name: "<<name << endl;

    // Init Shm
    // Write to Shm:
    key_t key = ftok("shmfile",65);
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096,0666|IPC_CREAT);
    // shmat to attach to shared memory
    EMPLOYEE_DATA_T *pShMem = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);

    int asmScore = 0, cppScore = 0, jsScore = 0, qmlScore = 0, openglSccore = 0;
    E_GET_SCORE_DATA_RESULT eResult = E_GET_SCORE_DATA_RESULLT_FAILED;
    for (int i = 0; i < EMPLOYEE_IN_LIST_MODEL_MAX; ++i) {
//        cout << pShMem[i].name << endl;
        if (strncmp(name.c_str(), pShMem[i].name, EMPLOYEE_NAME_MAXSIZE-1) == 0) {
            cout << "[AvnService] " << __func__ << " Matched!" << endl;
            asmScore = pShMem[i].asmScore;
            cppScore = pShMem[i].cppScore;
            jsScore = pShMem[i].jsScore;
            qmlScore = pShMem[i].qmlScore;
            openglSccore = pShMem[i].openglScore;
            eResult = E_GET_SCORE_DATA_RESULLT_OK;
            break;
        }
    }
    // deploy onResponse to client
    m_deploy->onResponseScoreDataToC(eResult, asmScore, cppScore, jsScore, qmlScore, openglSccore);
}

void AvnService::requestUpdateData(const string &name, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
{
    cout << "[AvnService] "<<__func__ << " >> "
            << "name: " << name
            << "asmScore: " << asmScore
            << "cppScore: " << cppScore
            << "jsScore: " << jsScore
            << "qmlScore: " << qmlScore
            << "openglScore: " << openglScore << endl;

    // Init Shm
    // Write to Shm:
    key_t key = ftok("shmfile",65);
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096,0666|IPC_CREAT);
    // shmat to attach to shared memory
    EMPLOYEE_DATA_T *pShMem = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);

    E_UPDATE_DATA_RESULT eResult = E_UPDATE_DATA_RESULLT_FAILED;
    for (int i = 0; i < EMPLOYEE_IN_LIST_MODEL_MAX; ++i) {
//        cout << pShMem[i].name << endl;
        if (strncmp(name.c_str(), pShMem[i].name, EMPLOYEE_NAME_MAXSIZE-1) == 0) {
            cout << "[AvnService] " << __func__ << " Matched!" << endl;
            pShMem[i].asmScore = asmScore;
            pShMem[i].cppScore = cppScore;
            pShMem[i].jsScore = jsScore;
            pShMem[i].qmlScore = qmlScore;
            pShMem[i].openglScore = openglScore;
            eResult = E_UPDATE_DATA_RESULLT_OK;
            break;
        }
    }
    // deploy onResponse to client
    m_deploy->onResponseUpdateData(eResult);
    // notify to all client relate
    m_deploy->onNotifyDataChanged();
}

void AvnService::requestGetScoreDataFromA(const int &id, const string &name)
{
    cout << "[AvnService] "<<__func__ << "id: "<<id << " name: "<<name << endl;

    // Init Shm
    // Write to Shm:
    key_t key = ftok("shmfile",65);
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096,0666|IPC_CREAT);
    // shmat to attach to shared memory
    EMPLOYEE_DATA_T *pShMem = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);

    int asmScore = 0, cppScore = 0, jsScore = 0, qmlScore = 0, openglSccore = 0;
    E_GET_SCORE_DATA_RESULT eResult = E_GET_SCORE_DATA_RESULLT_FAILED;
    for (int i = 0; i < EMPLOYEE_IN_LIST_MODEL_MAX; ++i) {
//        cout << pShMem[i].name << endl;
        if (strncmp(name.c_str(), pShMem[i].name, EMPLOYEE_NAME_MAXSIZE-1) == 0) {
            cout << "[AvnService] " << __func__ << " Matched!" << endl;
            asmScore = pShMem[i].asmScore;
            cppScore = pShMem[i].cppScore;
            jsScore = pShMem[i].jsScore;
            qmlScore = pShMem[i].qmlScore;
            openglSccore = pShMem[i].openglScore;
            eResult = E_GET_SCORE_DATA_RESULLT_OK;
            break;
        }
    }
    // deploy onResponse to client
    m_deploy->onResponseScoreDataToA(eResult, asmScore, cppScore, jsScore, qmlScore, openglSccore);
}

thread AvnService::runMqReceiveLooper()
{
    cout << "[AvnService] " << __func__ << endl;

    MQ_MSG_DATA_T mqMsgBuffer;
    memset(mqMsgBuffer.msg_text, 0x0, sizeof(mqMsgBuffer.msg_text));
    mqMsgBuffer.msg_type = E_MQ_MSG_TYPE_FOR_SERVICE;
    cout << "[AvnService] " << __func__ << " with msgId = " << m_mqHandler->getMsgId() << endl;
    while (1)
    {
        if (m_mqHandler->received(mqMsgBuffer) > 0)
        {
            E_MQ_MSG_APP_SERVICE_ID eClientID;
            int funcId;
            sscanf(mqMsgBuffer.msg_text, "%d %d", &eClientID, &funcId);
            cout << "[AvnService] "<<__func__ << "eClientID: "<<eClientID << endl;
            cout << "[AvnService] "<<__func__ << "funcId: "<<funcId << endl;

            if (eClientID == E_MQ_MSG_APPLICATION_A_ID) {
                switch (funcId) {
                case E_MQ_MSG_SERVICE_FUNC_ID_requestGetScoreDataFromA:
                {
                    int empId;
                    char empName[100];
                    sscanf(mqMsgBuffer.msg_text, "%d %d %d %s", &eClientID, &funcId, &empId, empName);
                    requestGetScoreDataFromA(empId, string(empName));
                }
                    break;
                default:
                    break;
                }
            }
            else if (eClientID == E_MQ_MSG_APPLICATION_C_ID) {
                switch (funcId) {
                case E_MQ_MSG_SERVICE_FUNC_ID_requestGetScoreDataFromC:
                {
                    int empId;
                    char empName[100];
                    sscanf(mqMsgBuffer.msg_text, "%d %d %d %s", &eClientID, &funcId, &empId, empName);
                    requestGetScoreDataFromC(empId, string(empName));
                }
                    break;
                case E_MQ_MSG_SERVICE_FUNC_ID_requestUpdateData:
                {
                    char empName[100];
                    int asmScore, cppScore, jsScore, qmlScore, openglScore;
                    sscanf(mqMsgBuffer.msg_text, "%d %d %s %d %d %d %d %d", &eClientID, &funcId, empName, &asmScore, &cppScore, &jsScore, &qmlScore, &openglScore);
                    requestUpdateData(string(empName), asmScore, cppScore, jsScore, qmlScore, openglScore);
                }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
