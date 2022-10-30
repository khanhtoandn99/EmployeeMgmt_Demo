#ifndef EMPLOYEEDATALIST_H
#define EMPLOYEEDATALIST_H

#include <QObject>

class EmployeeDataList
{
public:
    explicit EmployeeDataList(const QString &name = ""
                            ,const int &asmScore = 0
                            ,const int &cppScore = 0
                            ,const int &jsScore = 0
                            ,const int &qmlScore = 0
                            ,const int &openglScore = 0
                            ,const bool &isSelected = false);

    bool setName(const QString &name);
    bool setAsmScore(const int &asmScore);
    bool setCppScore(const int &cppScore);
    bool setJsScore(const int &jsScore);
    bool setQmlScore(const int &qmlScore);
    bool setOpenglScore(const int &openglScore);
    bool setSelectedState(const bool &isSelected);

    QString getName();
    int getAsmScore();
    int getCppScore();
    int getJsScore();
    int getQmlScore();
    int getOpenglScore();
    bool getSelectedState();

signals:

private:
    QString prvName;
    int prvAsmScore;
    int prvCppScore;
    int prvJsScore;
    int prvQmlScore;
    int prvOpenglScore;
    bool prvIsSelected;
};

#endif // EMPLOYEEDATALIST_H
