// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#define MAX 10

struct MQ_MSG_DATA_T {
    long mesg_type;
    char mesg_text[100];
};
  
int main()
{
    key_t key;
    int msgid;
    MQ_MSG_DATA_T message;
  
    // // ftok to generate unique key
    key = ftok("/home/avn/Desktop/LG_AVN_TEST/Framework/AVNService/progfile_service", 75);
    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("New msgid = %d\n", msgid);

    // message.mesg_type = E_MQ_MSG_TYPE_REQUESTGETSCOREDATA;
    message.mesg_type = 4;
    memcpy(message.mesg_text, "Framework/AVNService", sizeof("Framework/AVNService"));
  
    // msgsnd to send message
    int result = msgsnd(13, &message, sizeof(message.mesg_text), 0);

    if (result == -1) printf("Failed\n");


     // display the message
    printf("Data send is : %s \n", message.mesg_text);
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}