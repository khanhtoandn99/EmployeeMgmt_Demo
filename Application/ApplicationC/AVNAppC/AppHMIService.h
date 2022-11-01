#ifndef APPHMISERVICE_H
#define APPHMISERVICE_H

#include <QObject>
#include <QQuickView>
#include <qdebug.h>
#include <pthread.h>

#include "MqHandler.h"
#include "common.h"
#include "common_ipc.h"

class AppHMIService : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(bool m_ueConnected READ isConnected WRITE setConnected NOTIFY ueConnectedChanged)
public:
    explicit AppHMIService(QObject *parent = nullptr);
    void run();

public:
    Q_INVOKABLE void requestGetScoreData(const int &id, const QString &name);

    void onResponseScoreData(const E_GET_SCORE_DATA_RESULT &eResult, const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

signals:
    void signalUpdateScoreModel(const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

private:
    void runMqReceiveLooper();

    MqHandler *m_mqHandler;
};

#endif // APPHMISERVICE_H
