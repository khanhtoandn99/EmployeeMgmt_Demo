#ifndef EMPLOYEEDATAMODEL_H
#define EMPLOYEEDATAMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QAbstractListModel>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <employeedataitem.h>


class EmployeeDataModel: public QAbstractListModel
{
public:
    EmployeeDataModel(QObject *parent = nullptr): QAbstractListModel(parent){}

    enum E_EMPLOYEE_DATA_ROLES {
        NameRole = Qt::UserRole + 1,
        AsmScoreRole,
        CppScoreRole,
        JsScoreRole,
        QmlScoreRole,
        OpenGLScoreRole
    };

private:
    QList<EmployeeDataItem> prvEmployeeDataList;
};

#endif // EMPLOYEEDATAMODEL_H
