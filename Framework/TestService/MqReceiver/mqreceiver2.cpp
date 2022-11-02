// C Program for Message Queue (Reader Process)
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
  
enum E_MQ_MSG_TYPE : long
{
    E_MQ_MSG_TYPE_SET,
    E_MQ_MSG_TYPE_GET,
    E_MQ_MSG_TYPE_ON
};
// structure for message queue
struct MQ_MSG_DATA_T {
    E_MQ_MSG_TYPE mesg_type;
    char mesg_text[100];
};
  
int main()
{
    key_t key;
    int msgid;
    MQ_MSG_DATA_T message;
  
    // ftok to generate unique key
    key = ftok("/home/avn/Desktop/progfile2", 70);
    msgid = msgget(key, 0666 | IPC_CREAT);
    printf("New msgid = %d\n", msgid);
    
    while (1)
    {
        // msgrcv to receive message
        ssize_t ssize = msgrcv(msgid, &message, sizeof(message), 1, 0);

        if (ssize > 0) {
            // display the message
            printf("2.Data Received is : %s \n", message.mesg_text);

            memset(&message, 0x0, sizeof(MQ_MSG_DATA_T));
            memcpy(message.mesg_text, "Pong!", sizeof("Pong!"));

            
        }
    }
  
    return 0;
}