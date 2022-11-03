#ifndef APPHMISERVICE_H
#define APPHMISERVICE_H

#include <QObject>
#include <QQuickView>
#include <qdebug.h>
#include <QThread>
#include <pthread.h>

#include "MqHandler.h"
#include "common.h"

class AppHMIService :public QThread /*: public QObject*/
{
    Q_OBJECT
//    Q_PROPERTY(bool m_ueConnected READ isConnected WRITE setConnected NOTIFY ueConnectedChanged)
public:
    explicit AppHMIService(QObject *parent = nullptr);

    virtual void run();
    void runMqReceiveLooper();

    // IPC to Service
    Q_INVOKABLE void requestGetScoreDataFromC(const int &id, const QString &name);

    // IPC from service
    void onResponseScoreDataToC(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

signals:
    void signalUpdateScoreModel(const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

private: // Func

private: // Var/proxy
    MqHandler *m_mqHandler;
};

#endif // APPHMISERVICE_H
