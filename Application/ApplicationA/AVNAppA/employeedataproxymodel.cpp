#include "employeedataproxymodel.h"
#include <QtDebug>
#include <QtQml>

EmployeeDataProxyModel::EmployeeDataProxyModel(QObject *parent) : QSortFilterProxyModel(parent), m_complete(false)
{
    connect(this, &QSortFilterProxyModel::rowsInserted, this, &EmployeeDataProxyModel::countChanged);
    connect(this, &QSortFilterProxyModel::rowsRemoved, this, &EmployeeDataProxyModel::countChanged);
}

int EmployeeDataProxyModel::count() const
{
    return rowCount();
}

QObject *EmployeeDataProxyModel::source() const
{
    return sourceModel();
}

void EmployeeDataProxyModel::setSource(QObject *source)
{
    setSourceModel(qobject_cast<QAbstractItemModel *>(source));
}

QByteArray EmployeeDataProxyModel::sortRole() const
{
    return m_sortRole;
}

void EmployeeDataProxyModel::setSortRole(const QByteArray &role)
{
    if (m_sortRole != role) {
        m_sortRole = role;
        if (m_complete)
            QSortFilterProxyModel::setSortRole(roleKey(role));
    }
}

void EmployeeDataProxyModel::setSortOrder(Qt::SortOrder order)
{
    QSortFilterProxyModel::sort(0, order);
}

QByteArray EmployeeDataProxyModel::filterRole() const
{
    return m_filterRole;
}

void EmployeeDataProxyModel::setFilterRole(const QByteArray &role)
{
    if (m_filterRole != role) {
        m_filterRole = role;
        if (m_complete)
            QSortFilterProxyModel::setFilterRole(roleKey(role));
    }
}

QString EmployeeDataProxyModel::filterString() const
{
    return filterRegExp().pattern();
}

void EmployeeDataProxyModel::setFilterString(const QString &filter)
{
    setFilterRegExp(QRegExp(filter, filterCaseSensitivity(), static_cast<QRegExp::PatternSyntax>(filterSyntax())));
}

EmployeeDataProxyModel::FilterSyntax EmployeeDataProxyModel::filterSyntax() const
{
    return static_cast<FilterSyntax>(filterRegExp().patternSyntax());
}

void EmployeeDataProxyModel::setFilterSyntax(EmployeeDataProxyModel::FilterSyntax syntax)
{
    setFilterRegExp(QRegExp(filterString(), filterCaseSensitivity(), static_cast<QRegExp::PatternSyntax>(syntax)));
}

QJSValue EmployeeDataProxyModel::get(int idx) const
{
    QJSEngine *engine = qmlEngine(this);
    QJSValue value = engine->newObject();
    if (idx >= 0 && idx < count()) {
        QHash<int, QByteArray> roles = roleNames();
        for (auto it = roles.cbegin(), end = roles.cend(); it != end; ++it)
            value.setProperty(QString::fromUtf8(it.value()), data(index(idx, 0), it.key()).toString());
    }
    return value;
}

void EmployeeDataProxyModel::classBegin()
{
}

void EmployeeDataProxyModel::componentComplete()
{
    m_complete = true;
    if (!m_sortRole.isEmpty())
        QSortFilterProxyModel::setSortRole(roleKey(m_sortRole));
    if (!m_filterRole.isEmpty())
        QSortFilterProxyModel::setFilterRole(roleKey(m_filterRole));
}

int EmployeeDataProxyModel::roleKey(const QByteArray &role) const
{
    return roleNames().key(role, -1);
}

QHash<int, QByteArray> EmployeeDataProxyModel::roleNames() const
{
    if (QAbstractItemModel *source = sourceModel())
        return source->roleNames();
    return QHash<int, QByteArray>();
}

bool EmployeeDataProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QRegExp rx = filterRegExp();
    if (rx.isEmpty())
        return true;
    QAbstractItemModel *model = sourceModel();
    if (filterRole().isEmpty()) {
        QHash<int, QByteArray> roles = roleNames();
        for (auto it = roles.cbegin(), end = roles.cend(); it != end; ++it) {
            QModelIndex sourceIndex = model->index(sourceRow, 0, sourceParent);
            QString key = model->data(sourceIndex, it.key()).toString();
            if (key.contains(rx))
                return true;
        }
        return false;
    }
    QModelIndex sourceIndex = model->index(sourceRow, 0, sourceParent);
    if (!sourceIndex.isValid())
        return true;
    QString key = model->data(sourceIndex, roleKey(filterRole())).toString();
    return key.contains(rx);
}
