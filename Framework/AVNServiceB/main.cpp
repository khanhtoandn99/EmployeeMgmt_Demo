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

// using namespace std;


void init();
void test();
void debug(EMPLOYEE_DATA_T *aEmpDataTmp);

int main()
{
    init();
    // test();
    return 0;
}

void init()
{
    std::cout << __func__ << std::endl;
    std::ifstream rfData(EMPLOYEE_DATA_MODEL_FILE_PATH);

    // Init Shm
    // Write to Shm:
    key_t key = ftok("shmfile",65);
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096,0666|IPC_CREAT);
    // shmat to attach to shared memory
    EMPLOYEE_DATA_T *pEmpDataPtr = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);

    // Read data from file and push to Shm
    std::string sLineData;
    EMPLOYEE_DATA_T *pEmpDataTmp;
    pEmpDataTmp = pEmpDataPtr;
    pEmpDataTmp = new EMPLOYEE_DATA_T[10];

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

    // debug(pEmpDataPtr);
    std::cout << "Data wrote to shared memory" << std::endl;

    debug(pEmpDataPtr);

    pEmpDataTmp = nullptr;


    //detach from shared memory 
    shmdt(pEmpDataTmp);

    while(1){}

    std::cout << __func__ << " end" << std::endl;

}

void debug(EMPLOYEE_DATA_T *aEmpDataTmp)
{
    std::cout << __func__ << "" << std::endl;
    if (aEmpDataTmp == nullptr) {std::cout << "nullptr"; return;}

    for (int i = 0; i < 10; ++i) {
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

void test()
{
    // shared memory ver2
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key,4096,0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    EMPLOYEE_DATA_T *pEmpDataPtr = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);
  
    EMPLOYEE_DATA_T empData[2] = {{1,"toan4_nguyen",1,2,3,4,5,1.1,0}, {1,"luan1_pham",5,4,3,2,1,2.2,0}};
    memcpy(pEmpDataPtr, empData, sizeof(empData));
  
    std::cout << "Data wrote to shared memory" << std::endl;
      
    //detach from shared memory 
    shmdt(pEmpDataPtr);

    while(1){}
}