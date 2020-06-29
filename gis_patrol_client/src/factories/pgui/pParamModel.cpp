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
#include <pParamGroup.h>
#include <pParameter.h>
#include "pTreeItem.h"
#include "pParamModel.h"

ParametersModel::ParametersModel( const QMap< qint64, QSharedPointer< pParamGroup > >& paramGroups, QObject* parent )
    : QAbstractItemModel( parent ), _paramGroups( paramGroups ), _rootItem( new pTreeItem ) {
    qDebug() << __PRETTY_FUNCTION__;
    this->setupModel( paramGroups, _rootItem );
}

ParametersModel::~ParametersModel() {
    delete _rootItem;
}

int ParametersModel::columnCount( const QModelIndex& parent) const {
    Q_UNUSED( parent );
    return _rootItem->columnCount();
}

int ParametersModel::rowCount( const QModelIndex& parent) const {
    pTreeItem *parentItem ( nullptr );
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<pTreeItem*>(parent.internalPointer());

    int nr = parentItem->childCount();
//    qDebug() << __PRETTY_FUNCTION__ << nr;
    return nr;
}

QModelIndex ParametersModel::index(int row, int column, const QModelIndex& parent) const {
//    qDebug() << __PRETTY_FUNCTION__ << row << column << parent;
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    pTreeItem *parentItem = getItem(parent);
    if(!parentItem)
        return QModelIndex();

    pTreeItem *childItem = parentItem->child(row);
    if (childItem) {
        QModelIndex wIndex = createIndex(row, column, childItem);
//        qDebug() << __PRETTY_FUNCTION__ << row << column << parent << wIndex;
        return wIndex;
    }
    return QModelIndex();
}

QModelIndex ParametersModel::parent(const QModelIndex& index) const {
    if (!index.isValid())
        return QModelIndex();

    pTreeItem *childItem = getItem( index );
    //static_cast<pTreeItem*>(index.internalPointer());
    pTreeItem *parentItem = childItem ? childItem->parentItem() : nullptr;

    if (!parentItem || parentItem == _rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant ParametersModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    pTreeItem* wItem = static_cast<pTreeItem*>(index.internalPointer());
    if( role == Qt::UserRole+USER_ENTITY ) {
        //if( wItem == nullptr || wItem->isNull())
        //    return -1;

        //qDebug() << __PRETTY_FUNCTION__ << wItem;
        return 1;//wItem->getEntity();
    }
    else if( role == Qt::UserRole ) {
        //qDebug() << __PRETTY_FUNCTION__ << wItem << wItem->isGroup() << QSharedPointer<pParamGroup>(wItem->getGroup()).isNull();
        if( !wItem || wItem->isNull() )
            return -1;

        return wItem->getId();
    }
    else if ( role == Qt::UserRole+1 ) {
        if( !wItem || wItem->isNull() )
            return QVariant();
        else if( wItem->getEntity() == 0 )
            return QVariant::fromValue< QSharedPointer<pParamGroup> >(wItem->getGroup());
        else if ( wItem->getEntity() == 1 )
            return QVariant::fromValue<QSharedPointer<pParameter> >(wItem->getParameter());
    }
    else if (role == Qt::DisplayRole)
        return wItem->data(index.column());

    return QVariant();
}

QVariant ParametersModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QStringList headers;
    headers << tr( "group name/parameter id" ) << tr( "Code" ) << tr( "Name" ) << tr( "Title" ) << tr( "Table name" ) << tr( "Column name" ) << tr( "Type" );
    if (section >= 0 && section < headers.size() && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers[section];

    return QVariant();
}

void ParametersModel::setupModel(const QMap< qint64, QSharedPointer< pParamGroup > >& paramGroups, pTreeItem* rootItem ) {
    if( paramGroups.isEmpty() )
        return;
    QVector< pTreeItem* > parents;
    parents << rootItem;
    for (QMap< qint64, QSharedPointer< pParamGroup > >::const_iterator ppg = paramGroups.constBegin();
            ppg != paramGroups.constEnd();
            ppg++) {
        //qDebug() << __PRETTY_FUNCTION__ << ppg.key() << ppg.value();
        if (ppg.value().isNull())
            continue;
        pTreeItem* ptr = new pTreeItem( ppg.value(), parents.last());
        int nchildren = ppg.value()->getChildGroups().size();
        if ( nchildren > 0) {
            setupModel( ppg.value()->getChildGroups(), ptr );
        }
        parents.last()->appendChild( ptr );
        QMap< qint64, QSharedPointer< pParameter >> pars = ppg.value()->getParameters();
        //qDebug() << __PRETTY_FUNCTION__ << "parameters from " << ppg.key() << ppg.value() << pars.size();
        for (QMap< qint64, QSharedPointer< pParameter >>::const_iterator ppa = pars.constBegin();
                ppa != pars.constEnd();
                ppa++) {
            if (ppa.value().isNull())
                continue;
            pTreeItem* pptr = new pTreeItem( ppa.value(), ptr);
            //qDebug() << __PRETTY_FUNCTION__ << ppa.key() << pptr->isGroup();
            ptr->appendChild( pptr );
        }
    }
}

Qt::ItemFlags ParametersModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool ParametersModel::setData(const QModelIndex &index, const QVariant &value,
             int role) {
    pTreeItem *item = getItem(index);
    if (!item)
        return false;

    if (role == Qt::UserRole+1) {
        QSharedPointer< pParamGroup > pgr = value.value< QSharedPointer< pParamGroup >>();
        if (pgr)
            item->setGroup( pgr );
        else {
            QSharedPointer< pParameter > ppar = value.value< QSharedPointer< pParameter >> ();
            item->setParameter( ppar );
        }
        emit dataChanged( index.sibling(index.row(), 0), index.sibling(index.row(), 6), {Qt::DisplayRole, Qt::EditRole, Qt::UserRole, Qt::UserRole+1});
        return true;
    }
    return false;
}

bool ParametersModel::insertRows(int position, int rows, const QModelIndex &parent) {
    pTreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem->insertChildren(position,
                                                    rows);
    endInsertRows();

    return success;
}

bool ParametersModel::removeRows(int position, int rows, const QModelIndex &parent) {
    pTreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

pTreeItem *ParametersModel::getItem(const QModelIndex &index) const {
    if (index.isValid()) {
        pTreeItem *item = static_cast<pTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return _rootItem;
}
