#include "employeedatalist.h"

EmployeeDataList::EmployeeDataList(const QString &name
                                   ,const double &averageScore
                                   ,const bool &isSelected)
{
    prvName = name;
    prvAverageScore = averageScore;
    prvIsSelected = isSelected;
}

// --------------------------------------------------- Set -------------------------------
bool EmployeeDataList::setName(const QString &name)
{
    if (prvName == name) return false;
    prvName = name;
    return true;
}

bool EmployeeDataList::setAverageScore(const double &averageScore)
{
    prvAverageScore = averageScore;
    return true;
}

bool EmployeeDataList::setSelectedState(const bool &isSelected)
{
    prvIsSelected = isSelected;
    return true;
}

// --------------------------------------------------- Get -------------------------------
QString EmployeeDataList::getName()
{
    return prvName;
}

double EmployeeDataList::getAverageScore()
{
    return prvAverageScore;
}

bool EmployeeDataList::getSelectedState()
{
    return prvIsSelected;
}

// -------------------------------------------------------------------------------

EmployeeDataDetailList::EmployeeDataDetailList(const int &score)
{
    prvScore = score;
}

bool EmployeeDataDetailList::setScore(const int &score)
{
    prvScore = score;
    return true;
}

int EmployeeDataDetailList::getScore()
{
    return prvScore;
}
