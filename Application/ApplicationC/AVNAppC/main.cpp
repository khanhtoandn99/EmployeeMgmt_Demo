#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "employeedatamodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<EmployeeDataModel>("EmpDataModel",1,0,"EmployeeDataModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

//    qmlRegisterType<EmployeeDataModel>("EmployeeDataModel",1,0,"EmployeeDataModel");

    engine.load(url);

    return app.exec();

}
