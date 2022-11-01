#include "AvnService.h"

AvnService::AvnService()
{
    std::cout << __func__ << std::endl;
    m_mqHandler = new MqHandler;
    m_deploy = new AvnDeploy;
    init();
}

AvnService::~AvnService()
{
    std::cout << __func__ << std::endl;
}
void AvnService::init()
{
    std::cout << __func__ << std::endl;
    loadEmpData();
}

void AvnService::start()
{
    std::cout << __func__ << std::endl;

    runMqReceiveLooper();
}


void AvnService::loadEmpData()
{
    std::cout << __func__ << std::endl;

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
        std::cout << "File: " << EMPLOYEE_DATA_MODEL_FILE_PATH << " open failed!" << std::endl;
    }

    memcpy(pShMem, pEmpDataTmp, sizeof(EMPLOYEE_DATA_T)*EMPLOYEE_IN_LIST_MODEL_MAX);

//    debugShm(pShMem);
    std::cout << "Data wrote to shared memory" << std::endl;
    delete[] pEmpDataTmp;
    pEmpDataTmp = nullptr;


    //detach from shared memory
    shmdt(pEmpDataTmp);

//    while(1){}

    std::cout << __func__ << " end" << std::endl;
}

void AvnService::debugShm(EMPLOYEE_DATA_T *aEmpDataTmp)
{
    std::cout << __func__ << "" << std::endl;
    if (aEmpDataTmp == nullptr) {std::cout << "nullptr"; return;}

    for (int i = 0; i < EMPLOYEE_IN_LIST_MODEL_MAX; ++i) {
        std::cout  << aEmpDataTmp[i].id << " "
                << aEmpDataTmp[i].name << " "
                << aEmpDataTmp[i].asmScore << " "
                << aEmpDataTmp[i].cppScore << " "
                << aEmpDataTmp[i].jsScore << " "
                << aEmpDataTmp[i].qmlScore << " "
                << aEmpDataTmp[i].openglScore << " "
                << aEmpDataTmp[i].average << " "
                << aEmpDataTmp[i].isSelected << std::endl;
    }
}

void AvnService::requestGetScoreData(const int &id, const string &name)
{
    printf("%s >> id: %d, name: %s\n", __func__, id, name.c_str());

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
            cout << "Matched!!!" << endl;
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
    m_deploy->onResponseScoreData(eResult, asmScore, cppScore, jsScore, qmlScore, openglSccore);
}

void AvnService::runMqReceiveLooper()
{
    cout << __func__ << std::endl;

    MQ_MSG_DATA_T mqMsgBuffer;
    while (1)
    {
        if (m_mqHandler->received(mqMsgBuffer) > 0)
        {
            char clientPath[100];
            sscanf(mqMsgBuffer.msg_text, "%s", clientPath);
            cout << "clientPath = " << clientPath << endl;
            cout << "msg_type = " << mqMsgBuffer.msg_type << endl;
            if (strncmp(clientPath, MQ_CLIENTPATH_AVNAPPA, MQ_MSG_DATA_MAX-1) == 0) {

            }
            else if (strncmp(clientPath, MQ_CLIENTPATH_AVNAPPC, MQ_MSG_DATA_MAX-1) == 0) {
                switch (mqMsgBuffer.msg_type) {
                case E_MQ_MSG_TYPE_REQUESTGETSCOREDATA:
                {
                    int id;
                    char name[100];
                    sscanf(mqMsgBuffer.msg_text, "%s %d %s", clientPath, &id, name);
                    requestGetScoreData(id, string(name));
                }
                    break;
                default:
                    cout << "Unknown mqMsgBuffer.msg_type" << std::endl;
                    break;
                }
            }
            else {
                cout << "Unknow client requested" << endl;
            }
            memset(&mqMsgBuffer, 0x0, sizeof(MQ_MSG_DATA_T));
        }
    }
}
