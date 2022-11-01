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
    case EMPLOYEE_DATA_ROLES_ID:
        return QString(employeeListItem.id);
        break;
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
    roles[EMPLOYEE_DATA_ROLES_ID] = "employeeId";
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

    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,4096,0666|IPC_CREAT);
    EMPLOYEE_DATA_T *empDataPtr = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);

    EMPLOYEE_LIST_ITEM_T empListItemTmp;
    if (empDataPtr == nullptr) {
        qDebug() << "empDataPtr is nullptr";
        return;
    }
    EMPLOYEE_DATA_T aEmpDataTmp[10];
    memcpy(aEmpDataTmp, empDataPtr, sizeof(EMPLOYEE_DATA_T)*10);

    for (int i = 0; i < 10; ++i)
    {
        empListItemTmp.id = aEmpDataTmp[i].id;
        empListItemTmp.name = QString::fromUtf8(aEmpDataTmp[i].name);
        empListItemTmp.averageScore = aEmpDataTmp[i].average;
        empListItemTmp.isSelected = aEmpDataTmp[i].isSelected;
        qDebug("empListItemTmp.id = %d", empListItemTmp.id);
        qDebug() << "empListItemTmp.name = " << empListItemTmp.name;
        qDebug("empListItemTmp.averageScore = %.2f", empListItemTmp.averageScore);
        qDebug("empListItemTmp.isSelected = %d", empListItemTmp.isSelected);
        vEmployeeList.push_back(empListItemTmp);
    }
    qDebug("Init data from Shm completed");
    endResetModel();

    //detach from shared memory
    shmdt(empDataPtr);

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

    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,4096,0666|IPC_CREAT);
    EMPLOYEE_DATA_T *empDataPtr = (EMPLOYEE_DATA_T*) shmat(shmid,(void*)0,0);

    beginResetModel();
    vEmployeeScore.clear();
    vEmployeeScore.push_back(empDataPtr[0].asmScore); // Asm score
    vEmployeeScore.push_back(empDataPtr[0].cppScore); // Cpp score
    vEmployeeScore.push_back(empDataPtr[0].jsScore); // Js score
    vEmployeeScore.push_back(empDataPtr[0].qmlScore); // Qml score
    vEmployeeScore.push_back(empDataPtr[0].openglScore); // OpenGl score
    endResetModel();

    //detach from shared memory
    shmdt(empDataPtr);
}

void EmployeeDataDetailModel::updateDetailData(const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
{
    // Send IPC to Service
    // onResponse from Service

    // Emit signal to EmployeeDataDetailModel
    beginResetModel();
    vEmployeeScore.clear();
    vEmployeeScore.push_back(asmScore); // Asm score
    vEmployeeScore.push_back(cppScore); // Cpp score
    vEmployeeScore.push_back(jsScore); // Js score
    vEmployeeScore.push_back(qmlScore); // Qml score
    vEmployeeScore.push_back(openglScore); // OpenGl score
    endResetModel();
}

void EmployeeDataDetailModel::slotUpdateScoreModel(const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore)
{
    beginResetModel();
    vEmployeeScore.clear();
    vEmployeeScore.push_back(asmScore); // Asm score
    vEmployeeScore.push_back(cppScore); // Cpp score
    vEmployeeScore.push_back(jsScore); // Js score
    vEmployeeScore.push_back(qmlScore); // Qml score
    vEmployeeScore.push_back(openglScore); // OpenGl score
    endResetModel();
}
