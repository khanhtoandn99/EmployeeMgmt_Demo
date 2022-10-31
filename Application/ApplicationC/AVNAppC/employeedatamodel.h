#ifndef EMPLOYEEDATAMODEL_H
#define EMPLOYEEDATAMODEL_H

#include <QAbstractListModel>
#include "employeedatalist.h"

class EmployeeDataModel : public QAbstractListModel
{
Q_OBJECT
signals:
    void signalUpdateDetailData(const int &asmScore, const int &cppScore, const int &jsScore, const int &qmlScore, const int &openglScore);

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
        EMPLOYEE_DATA_ROLES_AVERAGE_SCORE,
        EMPLOYEE_DATA_ROLES_IS_SELECTED
    };

    void init();

private:
    QList<EmployeeDataList> prvEmployeeDataList;
};


class EmployeeDataDetailModel : public QAbstractListModel
{
Q_OBJECT
public:
    explicit EmployeeDataDetailModel(QObject *parent = nullptr);

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
        EMPLOYEE_DATA_DETAIL_ROLES_SCORE = Qt::UserRole + 1,
    };

    void init();

    Q_INVOKABLE void updateDetailData(const QString &name)
    {
        qDebug("Q_INVOKABLE void EmployeeDataDetailModel::updateDetailData()");
        // Send IPC to Service
        // onResponse from Service

        // Emit signal to EmployeeDataDetailModel
        beginResetModel();
        vEmpScore.clear();
        vEmpScore.push_back(rand()); // Asm score
        vEmpScore.push_back(rand()); // Cpp score
        vEmpScore.push_back(rand()); // Js score
        vEmpScore.push_back(rand()); // Qml score
        vEmpScore.push_back(rand()); // OpenGl score
        endResetModel();
    }

private:
//    QList<EmployeeDataDetailList> prvEmployeeDataDetailList;
    QVector<int> vEmpScore;
};

#endif // EMPLOYEEDATAMODEL_H
