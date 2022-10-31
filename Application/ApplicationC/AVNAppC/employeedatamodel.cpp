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
    return prvEmployeeDataList.length();
}

QVariant EmployeeDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    EmployeeDataList empDataList = prvEmployeeDataList[index.row()];
    switch (role) {
    case EMPLOYEE_DATA_ROLES_NAME:
        return QString(empDataList.getName());
        break;
    case EMPLOYEE_DATA_ROLES_ASM_SCORE:
        return QVariant(empDataList.getAsmScore());
        break;
    case EMPLOYEE_DATA_ROLES_CPP_SCORE:
        return QVariant(empDataList.getCppScore());
        break;
    case EMPLOYEE_DATA_ROLES_JS_SCORE:
        return QVariant(empDataList.getJsScore());
        break;
    case EMPLOYEE_DATA_ROLES_QML_SCORE:
        return QVariant(empDataList.getQmlScore());
        break;
    case EMPLOYEE_DATA_ROLES_OPENGL_SCORE:
        return QVariant(empDataList.getOpenglScore());
        break;
    case EMPLOYEE_DATA_ROLES_AVERAGE_SCORE:
        return QVariant(empDataList.getAverageScore());
        break;
    case EMPLOYEE_DATA_ROLES_IS_SELECTED:
        return QVariant(empDataList.getSelectedState());
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
    roles[EMPLOYEE_DATA_ROLES_ASM_SCORE] = "asmScore";
    roles[EMPLOYEE_DATA_ROLES_CPP_SCORE] = "cppScore";
    roles[EMPLOYEE_DATA_ROLES_JS_SCORE] = "jsScore";
    roles[EMPLOYEE_DATA_ROLES_QML_SCORE] = "qmlScore";
    roles[EMPLOYEE_DATA_ROLES_OPENGL_SCORE] = "openglScore";
    roles[EMPLOYEE_DATA_ROLES_AVERAGE_SCORE] = "averageScore";
    roles[EMPLOYEE_DATA_ROLES_IS_SELECTED] = "isSelected";

    return roles;
}

void EmployeeDataModel::init()
{
    qDebug("EmployeeDataModel::init()");
    prvEmployeeDataList.append(EmployeeDataList("toan4.nguyen", 5, 4, 3, 2, 1, 1.1, false));
    prvEmployeeDataList.append(EmployeeDataList("luan1.pham", 1, 2, 3, 4, 5, 1.2, false));
    prvEmployeeDataList.append(EmployeeDataList("hoang1.nguyen", 5, 4, 3, 2, 1, 1.3, false));
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    endInsertRows();
}
