#ifndef COMMON_IPC_H
#define COMMON_IPC_H

#include <iostream>

// For Message Queue:
#define MQ_FTOK_KEY_APPA_FILEPATH "/home/avn/Desktop/LG_AVN_TEST/Application/ApplicationA/AVNAppA/progfile_appa"
#define MQ_FTOK_KEY_APPA_ID 65

#define MQ_FTOK_KEY_APPC_FILEPATH "/home/avn/Desktop/LG_AVN_TEST/Application/ApplicationC/AVNAppC/progfile_appc"
#define MQ_FTOK_KEY_APPC_ID 70

#define MQ_FTOK_KEY_SERVICE_FILEPATH "/home/avn/Desktop/LG_AVN_TEST/Framework/AVNService/progfile_service"
#define MQ_FTOK_KEY_SERVICE_ID 75

#define MQ_APP_SERVICE_NUM 3

#define MQ_MSG_DATA_MAX 100 //bytes

#define MQ_CLIENTPATH_AVNAPPA "Application/AVNAppA"
#define MQ_CLIENTPATH_AVNAPPC "Application/AVNAppC"
#define MQ_CLIENTPATH_AVNSERVICE "Framework/AVNService"

// For Message Queue:
enum E_MQ_MSG_TYPE : long // long type is important for MQ
{
    E_MQ_MSG_TYPE_NEGATIVE = -1, // first message in the queue with the lowest type less than or equal to the absolute value of msgtyp will be read
    E_MQ_MSG_TYPE_0 = 0, // first message in the queue is read.
    E_MQ_MSG_TYPE_1 = 1, // > 1 ==> first message in the queue of type msgtyp is read (common use)
    E_MQ_MSG_TYPE_FOR_APP_A,
    E_MQ_MSG_TYPE_FOR_APP_C,
    E_MQ_MSG_TYPE_FOR_SERVICE,
    E_MQ_MSG_TYPE_NUM
};

enum E_MQ_MSG_APP_SERVICE_ID
{
    E_MQ_MSG_APPLICATION_A_ID = 1,
    E_MQ_MSG_APPLICATION_C_ID,
    E_MQ_MSG_SERVICE_B_ID,
    E_MQ_MSG_APP_SERVICE_NUM
};

enum E_MQ_MSG_APP_A_FUNC_ID
{
    // To Service:

    // To proxy:
    E_MQ_MSG_APP_A_FUNC_ID_NUM
};

enum E_MQ_MSG_APP_C_FUNC_ID
{
    // To Service:

    // To Proxy:
    E_MQ_MSG_APP_C_FUNC_ID_NUM
};

enum E_MQ_MSG_SERVICE_FUNC_ID
{
    // To Service:
    E_MQ_MSG_SERVICE_FUNC_ID_requestGetScoreDataFromA = 1,
    E_MQ_MSG_SERVICE_FUNC_ID_requestGetScoreDataFromC,
    E_MQ_MSG_SERVICE_FUNC_ID_requestUpdateData,

    // To Proxy:
    E_MQ_MSG_SERVICE_FUNC_ID_onResponseScoreDataToA,
    E_MQ_MSG_SERVICE_FUNC_ID_onResponseScoreDataToC,
    E_MQ_MSG_SERVICE_FUNC_ID_onResponseUpdateData,
    E_MQ_MSG_SERVICE_FUNC_ID_requestSaveDataOnExit,

    // TO proxySync
    E_MQ_MSG_SERVICE_FUNC_ID_onNotifyDataChanged,

    E_MQ_MSG_SERVICE_FUNC_ID_NUM
};

typedef struct
{
    key_t key;
    int keyId;

} MQ_MSG_KEY_T;

typedef struct
{
    long msg_type;
    char msg_text[100];

} MQ_MSG_DATA_T;

#endif // COMMON_IPC_H
