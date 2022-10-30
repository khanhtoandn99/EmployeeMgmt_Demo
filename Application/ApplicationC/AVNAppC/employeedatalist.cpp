#include "employeedatalist.h"

EmployeeDataList::EmployeeDataList(const QString &name
                                   ,const int &asmScore
                                   ,const int &cppScore
                                   ,const int &jsScore
                                   ,const int &qmlScore
                                   ,const int &openglScore
                                   ,const bool &isSelected)
{
    prvName = name;
    prvAsmScore = asmScore;
    prvCppScore = cppScore;
    prvJsScore = jsScore;
    prvQmlScore = qmlScore;
    prvOpenglScore = openglScore;
    prvIsSelected = isSelected;
}

// --------------------------------------------------- Set -------------------------------
bool EmployeeDataList::setName(const QString &name)
{
    if (prvName == name) return false;
    prvName = name;
    return true;
}

bool EmployeeDataList::setAsmScore(const int &asmScore)
{
    prvAsmScore = asmScore;
    return true;
}

bool EmployeeDataList::setCppScore(const int &cppScore)
{
    prvCppScore = cppScore;
    return true;
}

bool EmployeeDataList::setJsScore(const int &jsScore)
{
    prvJsScore = jsScore;
    return true;
}

bool EmployeeDataList::setQmlScore(const int &qmlScore)
{
    prvQmlScore = qmlScore;
    return true;
}

bool EmployeeDataList::setOpenglScore(const int &openglScore)
{
    prvOpenglScore = openglScore;
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

int EmployeeDataList::getAsmScore()
{
    return prvAsmScore;
}

int EmployeeDataList::getCppScore()
{
    return prvCppScore;
}

int EmployeeDataList::getJsScore()
{
    return prvJsScore;
}

int EmployeeDataList::getQmlScore()
{
    return prvQmlScore;
}

int EmployeeDataList::getOpenglScore()
{
    return prvOpenglScore;
}

bool EmployeeDataList::getSelectedState()
{
    return prvIsSelected;
}
