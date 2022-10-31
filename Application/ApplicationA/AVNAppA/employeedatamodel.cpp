#include "employeedatamodel.h"

EmployeeDataModel::EmployeeDataModel(QObject *parent)
    : QAbstractListModel(parent)
{
    init();
}

int EmployeeDataModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return vEmployeeList.size();
}

QVariant EmployeeDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    EMPLOYEE_LIST_ITEM_T employeeListItem = vEmployeeList[index.row()];
    switch (role) {
    case EMPLOYEE_DATA_ROLES_NAME:
        return QString(employeeListItem.name);
        break;
    case EMPLOYEE_DATA_ROLES_AVERAGE_SCORE:
        return QVariant(employeeListItem.averageScore);
        break;
    case EMPLOYEE_DATA_ROLES_IS_SELECTED:
        return QVariant(employeeListItem.isSelected);
        break;
    default:
        break;
    }
    return QVariant();
}

bool EmployeeDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags EmployeeDataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> EmployeeDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EMPLOYEE_DATA_ROLES_NAME] = "employeeName";
    roles[EMPLOYEE_DATA_ROLES_AVERAGE_SCORE] = "averageScore";
    roles[EMPLOYEE_DATA_ROLES_IS_SELECTED] = "isSelected";

    return roles;
}

void EmployeeDataModel::init()
{
    qDebug("EmployeeDataModel::init()");
    beginResetModel();

    vEmployeeList.clear();

    EMPLOYEE_LIST_ITEM_T empListItemTmp;
    empListItemTmp.name = "toan4.nguyen";
    empListItemTmp.averageScore = 1.1;
    empListItemTmp.isSelected = false;
    vEmployeeList.push_back(empListItemTmp);

    empListItemTmp.name = "tru.vu";
    empListItemTmp.averageScore = 2.2;
    vEmployeeList.push_back(empListItemTmp);

    empListItemTmp.name = "luan1.pham";
    empListItemTmp.averageScore = 3.3;
    vEmployeeList.push_back(empListItemTmp);

    empListItemTmp.name = "hoang1.nguyen";
    empListItemTmp.averageScore = 4.5;
    vEmployeeList.push_back(empListItemTmp);

    empListItemTmp.name = "viet.mac";
    empListItemTmp.averageScore = 5.5;
    vEmployeeList.push_back(empListItemTmp);

    empListItemTmp.name = "hau.truong";
    empListItemTmp.averageScore = 0.0;
    vEmployeeList.push_back(empListItemTmp);

    empListItemTmp.name = "phi.nguyen";
    empListItemTmp.averageScore = 2.3;
    vEmployeeList.push_back(empListItemTmp);

    endResetModel();
}



EmployeeDataDetailModel::EmployeeDataDetailModel(QObject *parent)
    : QAbstractListModel(parent)
{
    init();
}

int EmployeeDataDetailModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return vEmployeeScore.size();
}

QVariant EmployeeDataDetailModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    int empScore = vEmployeeScore[index.row()];
    switch (role) {
    case EMPLOYEE_DATA_DETAIL_ROLES_SCORE:
        return QVariant(empScore);
        break;
    default:
        break;
    }
    return QVariant();
}

bool EmployeeDataDetailModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags EmployeeDataDetailModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> EmployeeDataDetailModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[EMPLOYEE_DATA_DETAIL_ROLES_SCORE] = "skillScore";
    return roles;
}

void EmployeeDataDetailModel::init()
{
    qDebug("EmployeeDataDetailModel::init()");
    beginResetModel();
    vEmployeeScore.clear();
    vEmployeeScore.push_back(1); // Asm score
    vEmployeeScore.push_back(2); // Cpp score
    vEmployeeScore.push_back(3); // Js score
    vEmployeeScore.push_back(4); // Qml score
    vEmployeeScore.push_back(5); // OpenGl score
    endResetModel();
}
