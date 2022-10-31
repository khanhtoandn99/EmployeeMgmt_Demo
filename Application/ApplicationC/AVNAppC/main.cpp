#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "employeedatamodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<EmployeeDataModel>("EmpDataModel",1,0,"EmployeeDataModel");
    qmlRegisterType<EmployeeDataDetailModel>("EmpDataDetailModel",1,0,"EmployeeDataDetailModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();


//    // Method 2:

//    qmlRegisterType<EmployeeDataModel>("EmpDataModel",1,0,"EmployeeDataModel");
//    qmlRegisterType<EmployeeDataDetailModel>("EmpDataDetailModel",1,0,"EmployeeDataDetailModel");

//    EmployeeDataModel EmpDataModel;
//    EmployeeDataDetailModel EmpDataDetailModel;

//    QQuickView view;
//    QQmlContext *context = view.engine()->rootContext();
//    context->setContextProperty("EmployeeDataDetailModel", &EmpDataModel);

//    view.setSource(QUrl("qrc:main.qml"));
//    view.show();

//    return app.exec();

}
