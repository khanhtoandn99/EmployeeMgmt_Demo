#ifndef EMPLOYEEDATAMODEL_H
#define EMPLOYEEDATAMODEL_H

#include <QAbstractListModel>
#include "employeedatalist.h"

class EmployeeDataModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit EmployeeDataModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    // toan4.nguyen:
    enum EMPLOYEE_DATA_ROLES {
        EMPLOYEE_DATA_ROLES_NAME = Qt::UserRole + 1,
        EMPLOYEE_DATA_ROLES_ASM_SCORE,
        EMPLOYEE_DATA_ROLES_CPP_SCORE,
        EMPLOYEE_DATA_ROLES_JS_SCORE,
        EMPLOYEE_DATA_ROLES_QML_SCORE,
        EMPLOYEE_DATA_ROLES_OPENGL_SCORE,
        EMPLOYEE_DATA_ROLES_IS_SELECTED
    };

    void init();

private:
    QList<EmployeeDataList> prvEmployeeDataList;
};

#endif // EMPLOYEEDATAMODEL_H
