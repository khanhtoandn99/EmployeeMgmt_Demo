#ifndef APPHMISERVICE_H
#define APPHMISERVICE_H

#include <QObject>
#include <QQuickView>
#include <qdebug.h>

#include "MqHandler.h"

class AppHMIService : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(bool m_ueConnected READ isConnected WRITE setConnected NOTIFY ueConnectedChanged)
public:
    explicit AppHMIService(QObject *parent = nullptr);

public:
    Q_INVOKABLE void getEmpDetailData(const QString &name);

signals:

private:
    MqHandler *m_mqHandler;
};

#endif // APPHMISERVICE_H
