#include "customtablemodel.h"
#include <QtCore/QList>
#include <QtCore/QTime>
#include <QtCore/QRect>
#include <QtCore/QRandomGenerator>
#include <QtGui/QColor>

customtablemodel::customtablemodel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_columnCount = 2;
    m_rowCount = 12;

    // m_data
    for (int i = 0; i < m_rowCount; i++) {
        QList<qreal> *dataList = new QList<qreal>(m_columnCount);
        for (int k = 0; k < dataList->size(); k++) {
            if (k % 2 == 0)
                dataList->replace(k, i * 50 + QRandomGenerator::global()->bounded(20));
            else
                dataList->replace(k, QRandomGenerator::global()->bounded(100));
        }
        m_data.append(dataList);
    }
}

customtablemodel::~customtablemodel()
{
    qDeleteAll(m_data);
}

int customtablemodel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int customtablemodel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_columnCount;
}

QVariant customtablemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("201%1").arg(section);
    else
        return QString("%1").arg(section + 1);
}

QVariant customtablemodel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::EditRole) {
        return m_data[index.row()]->at(index.column());
    } else if (role == Qt::BackgroundRole) {
        for (const QRect &rect : m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }

        // cell not mapped return white color
        return QColor(Qt::white);
    }
    return QVariant();
}

bool customtablemodel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        m_data[index.row()]->replace(index.column(), value.toDouble());
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags customtablemodel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void customtablemodel::addMapping(QString color, QRect area)
{
    m_mapping.insert(color, area);
}
