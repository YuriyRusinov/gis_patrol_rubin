/*
 * @brief Класс, описывающий визуальную модель параметров, сгруппированных по подходящим пользовательским группам
 * pParamModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <defines.h>
#include <QtDebug>
#include <pParameter.h>
#include "pTreeItem.h"
#include "pCatParamModel.h"

pCatParametersModel::pCatParametersModel( const QMap< qint64, QSharedPointer< pCatParameter > >& paramGroups, QObject* parent )
    : QAbstractItemModel( parent ), _paramGroups( paramGroups ) {
    qDebug() << __PRETTY_FUNCTION__;
}

pCatParametersModel::~pCatParametersModel() {
}

int pCatParametersModel::columnCount( const QModelIndex& parent) const {
    Q_UNUSED( parent );
    return 4;
}

int pCatParametersModel::rowCount( const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;

    return _paramGroups.size();
}

QModelIndex pCatParametersModel::index(int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() )
        return QModelIndex();

    if (row >= 0 && row < _paramGroups.size() ) {
        QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _paramGroups.constBegin()+row;
        return createIndex(row, column, pct.value().get() );
    }
    return QModelIndex();
}

QModelIndex pCatParametersModel::parent(const QModelIndex& index) const {
    Q_UNUSED( index );
    return QModelIndex();
}

QVariant pCatParametersModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    int iRow = index.row();
    int iColumn = index.column();
    QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _paramGroups.constBegin()+row;
    if( role == Qt::UserRole ) {
        return pct.key();
    }
    else if ( role == Qt::UserRole+1 ) {
        return pct.value().isNull() ? QVariant() : QVariant::fromValue< QSharedPointer< pCatParameter > >(pct.value());
    }
    else if (role == Qt::DisplayRole) {
        if (pct.value().isNull())
            return QVariant();
        switch( iColumn ) {
            case 0: return pct.value()->getName(); break;
            case 1: return pct.value()->getDefaultValue(); break;
            default: return QVariant(); break;
        }
    }
    else if (role == Qt::CheckStateRole) {
        if (pct.value().isNull())
            return QVariant();
        switch( iColumn ) {
            case 2: return (pct.value()->isMandatory() ? Qt::Checked : Qt::Unchecked); break;
            case 3: return (pct.value()->isReadOnly() ? Qt::Checked : Qt::Unchecked); break;
            default: return QVariant(); break;
        }
    }

    return QVariant();
}

QVariant pCatParametersModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QStringList headers;
    headers << tr( "Name" ) << tr("Default Value") << tr( "Mandatory" ) << tr( "Read only" );
    if (section >= 0 && section < headers.size() && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers[section];

    return QVariant();
}

Qt::ItemFlags pCatParametersModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool pCatParametersModel::setData(const QModelIndex& index, const QVariant &value,
             int role) {
    if (!index.isValid())
        return false;

    QMap< qint64, QSharedPointer< pCatParameter > >::iterator pct = _paramGroups.constBegin() + index.row();
    if (role == Qt::UserRole+1) {
        QSharedPointer< pCatParameter > pgr = value.value< QSharedPointer< pCatParameter >>();
        if (pgr)
            item->setGroup( pgr );
        else {
            QSharedPointer< pParameter > ppar = value.value< QSharedPointer< pParameter >> ();
            item->setParameter( ppar );
        }
        emit dataChanged( index.sibling(index.row(), 0), index.sibling(index.row(), 4), {Qt::DisplayRole, Qt::EditRole, Qt::UserRole, Qt::UserRole+1});
        return true;
    }
    return false;
}

bool pCatParametersModel::insertRows(int position, int rows, const QModelIndex &parent) {
    pTreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows);
    endInsertRows();

    return success;
}

bool pCatParametersModel::removeRows(int position, int rows, const QModelIndex &parent) {
    pTreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}
