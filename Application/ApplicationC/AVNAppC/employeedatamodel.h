#ifndef EMPLOYEEDATAMODEL_H
#define EMPLOYEEDATAMODEL_H

#include <QObject>
#include <QAbstractListModel>

class TodoItem {
public:
    explicit TodoItem(const QString &content, const bool &isDone){
        pContent = content;
        pIsDone = isDone;
    };

    QString content() const{
        return pContent;
    }
    bool isDone()const{
        return pIsDone;
    }

    bool setContent(const QString &content){
        if(pContent == content){
            return false;
        }

        pContent = content;
        return true;
    }

    bool setIsDone(const bool &isDone){
        pIsDone = isDone;
        return true;
    }

private:
    QString pContent;
    bool pIsDone;
};

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
};

#endif // EMPLOYEEDATAMODEL_H
