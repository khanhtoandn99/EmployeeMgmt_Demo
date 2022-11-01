#ifndef COMMON_IPC_H
#define COMMON_IPC_H

#include <iostream>

// For Message Queue:
#define MQ_KEY_FTOK_FILEPATH "/home/avn/Desktop/LG_AVN_TEST/progfile"
#define MQ_MSG_DATA_MAX 100 //bytes

#define MQ_CLIENTPATH_AVNAPPA "Application/AVNAppA"
#define MQ_CLIENTPATH_AVNAPPC "Application/AVNAppC"
#define MQ_CLIENTPATH_AVNSERVICE "Application/AVNService"

// For Message Queue:
enum E_MQ_MSG_TYPE : long // long type is important for MQ
{
    E_MQ_MSG_TYPE_REQUESTGETSCOREDATA = 1,
    E_MQ_MSG_TYPE_ONRESPONSESCOREDATA,
};

typedef struct
{
    E_MQ_MSG_TYPE msg_type;
    char msg_text[100];

} MQ_MSG_DATA_T;

#endif // COMMON_IPC_H
