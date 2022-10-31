#ifndef EMPLOYEEDATALIST_H
#define EMPLOYEEDATALIST_H

#include <QObject>

class EmployeeDataList
{
public:
    explicit EmployeeDataList(const QString &name = ""
                            ,const double &averageScore = 0.0
                            ,const bool &isSelected = false);

    bool setName(const QString &name);
    bool setAverageScore(const double &averageScore);
    bool setSelectedState(const bool &isSelected);

    QString getName();
    double getAverageScore();
    bool getSelectedState();

signals:

private:
    QString prvName;
    double prvAverageScore;
    bool prvIsSelected;
};

class EmployeeDataDetailList
{
public:
    explicit EmployeeDataDetailList(const int &score = 0);

    bool setScore(const int &score);

    int getScore();

signals:

private:
    int prvScore;
};

#endif // EMPLOYEEDATALIST_H
