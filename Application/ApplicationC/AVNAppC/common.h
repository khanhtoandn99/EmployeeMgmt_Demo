#ifndef COMMON_H_
#define COMMON_H_

#include <QVariant>

#define EMPLOYEE_NAME_MAXSIZE 100
#define EMPLOYEE_IN_LIST_MODEL_MAX 10 // 10 employee data support

#define EMPLOYEE_DATA_MODEL_FILE_PATH "/home/avn/Desktop/LG_AVN_TEST/Framework/AVNService/empdatamodel.txt"

#define MQ_MSG_DATA_MAX 100 //bytes

typedef struct
{
    int id;
    char name[EMPLOYEE_NAME_MAXSIZE];
    int asmScore;
    int cppScore;
    int jsScore;
    int qmlScore;
    int openglScore;
    float average;
    bool isSelected;

} EMPLOYEE_DATA_T;

typedef struct
{
    QString name;
    double averageScore;
    bool isSelected;

} EMPLOYEE_LIST_ITEM_T;

#endif
