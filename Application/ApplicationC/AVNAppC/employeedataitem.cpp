#include "employeedataitem.h"

EmployeeDataItem::EmployeeDataItem(const QString &name
                                           ,const int &asmScore
                                           ,const int &cppScore
                                           ,const int &jsScore
                                           ,const int &qmlScore
                                           ,const int &openglScore)
{
    prvName = name;
    prvAsmScore = asmScore;
    prvCppScore = cppScore;
    prvJsScore = jsScore;
    prvQmlScore = qmlScore;
    prvOpenglScore = openglScore;
}

// --------------------------------------------------- Set -------------------------------
bool EmployeeDataItem::setName(const QString &name)
{
    if (prvName == name) return false;
    prvName = name;
    return true;
}

bool EmployeeDataItem::setAsmScore(const int &asmScore)
{
    prvAsmScore = asmScore;
    return true;
}

bool EmployeeDataItem::setCppScore(const int &cppScore)
{
    prvCppScore = cppScore;
    return true;
}

bool EmployeeDataItem::setJsScore(const int &jsScore)
{
    prvJsScore = jsScore;
    return true;
}

bool EmployeeDataItem::setQmlScore(const int &qmlScore)
{
    prvQmlScore = qmlScore;
    return true;
}

bool EmployeeDataItem::setOpenglScore(const int &openglScore)
{
    prvOpenglScore = openglScore;
    return true;
}

// --------------------------------------------------- Get -------------------------------
QString EmployeeDataItem::getName()
{
    return prvName;
}

int EmployeeDataItem::getAsmScore()
{
    return prvAsmScore;
}

int EmployeeDataItem::getCppScore()
{
    return prvCppScore;
}

int EmployeeDataItem::getJsScore()
{
    return prvJsScore;
}

int EmployeeDataItem::getQmlScore()
{
    return prvQmlScore;
}

int EmployeeDataItem::getOpenglScore()
{
    return prvOpenglScore;
}
