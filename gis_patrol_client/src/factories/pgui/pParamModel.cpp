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
    pTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<pTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

QModelIndex ParametersModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    pTreeItem *parentItem;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<pTreeItem*>(parent.internalPointer());

    pTreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex ParametersModel::parent(const QModelIndex& index) const {
    if (!index.isValid())
        return QModelIndex();

    pTreeItem *childItem = static_cast<pTreeItem*>(index.internalPointer());
    pTreeItem *parentItem = childItem->parentItem();

    if (parentItem == _rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

QVariant ParametersModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    pTreeItem* wItem = static_cast<pTreeItem*>(index.internalPointer());
    if( role == Qt::UserRole+USER_ENTITY ) {
        if( wItem->isGroup() )
            return 0;
        else
            return 1;
    }
    else if( role == Qt::UserRole ) {
        if( wItem->isGroup() )
            return wItem->getGroup()->getId();
        else if ( wItem->isParameter() )
            return wItem->getParameter()->getId();
    }
    else if (role == Qt::DisplayRole)
        return wItem->data(index.column());

    return QVariant();
}

QVariant ParametersModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QStringList headers;
    headers << tr( "Id" ) << tr( "Code" ) << tr( "Name" ) << tr( "Title" ) << tr( "Table name" ) << tr( "Column name" ) << tr( "Type" );
    if (section >= 0 && section < headers.size() && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers[section];

    return QVariant();
}

void ParametersModel::setupModel(const QMap< qint64, QSharedPointer< pParamGroup > >& paramGroups, pTreeItem* rootItem ) {
    QVector< pTreeItem* > parents;
    parents << rootItem;
    for (QMap< qint64, QSharedPointer< pParamGroup > >::const_iterator ppg = paramGroups.constBegin();
            ppg != paramGroups.constEnd();
            ppg++) {
        qDebug() << __PRETTY_FUNCTION__ << ppg.value();
        pTreeItem* ptr = new pTreeItem( ppg.value(), parents.last());
        parents.last()->appendChild( ptr );
        if (ppg.value()->getChildGroups().size() > 0) {
            setupModel( ppg.value()->getChildGroups(), ptr );
        }
        QMap< qint64, QSharedPointer< pParameter >> pars = ppg.value()->getParameters();
        for (QMap< qint64, QSharedPointer< pParameter >>::const_iterator ppa = pars.constBegin();
                ppa != pars.constEnd();
                ppa++) {
            pTreeItem* pptr = new pTreeItem( ppa.value(), ptr);
            ptr->appendChild( pptr );
        }
    }
}