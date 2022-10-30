#ifndef EMPLOYEEDATAITEM_H
#define EMPLOYEEDATAITEM_H


#include <QObject>
#include <QAbstractListModel>
#include <QAbstractListModel>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class EmployeeDataItem {
public:
    explicit EmployeeDataItem(const QString &name
                             ,const int &asmScore
                             ,const int &cppScore
                             ,const int &jsScore
                             ,const int &qmlScore
                             ,const int &openglScore);

    bool setName(const QString &name);
    bool setAsmScore(const int &asmScore);
    bool setCppScore(const int &cppScore);
    bool setJsScore(const int &jsScore);
    bool setQmlScore(const int &qmlScore);
    bool setOpenglScore(const int &openglScore);

    QString getName();
    int getAsmScore();
    int getCppScore();
    int getJsScore();
    int getQmlScore();
    int getOpenglScore();

private:
    QString prvName;
    int prvAsmScore;
    int prvCppScore;
    int prvJsScore;
    int prvQmlScore;
    int prvOpenglScore;
};

#endif // EMPLOYEEDATAITEM_H
