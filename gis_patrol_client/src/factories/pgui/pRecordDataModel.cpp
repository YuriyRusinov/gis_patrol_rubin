/* 
 * @brief Класс описывает визуальную модель отображения данных
 * pRecordDataModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QIcon>
#include <QModelIndex>
#include <QtDebug>

#include <pRecordC.h>
#include <pCatParameter.h>
#include <pCategory.h>
#include <pParamType.h>
#include <pParamValue.h>

#include "pRecTreeItem.h"
#include "pRecordDataModel.h"

pRecordDataModel::pRecordDataModel( QSharedPointer< pCategory > pCategory, const QMap< qint64, QSharedPointer< pRecordCopy > >& records, QObject* parent )
    : QAbstractItemModel( parent ),
    _rootItem( nullptr ),
    _pCategory( pCategory ),
    _records( records ),
    _cParamParent( nullptr ),
    _cParamBackground( nullptr ),
    _cParamForeground( nullptr ) {
    _cParamParent = getFirstParameter( pParamType::atParent );
    _cParamBackground = getFirstParameter( pParamType::atRecordColor );
    if( _cParamBackground.isNull() )
        _cParamBackground = getFirstParameter( pParamType::atRecordColorRef );
    _cParamForeground = getFirstParameter( pParamType::atRecordTextColor );
    if( _cParamForeground )
        _cParamForeground = getFirstParameter( pParamType::atRecordTextColorRef );
    setupParams();
    _rootItem = new pRecTreeItem( -1, QSharedPointer<const pRecordCopy>( nullptr ), _sortedParams );
    setupCategoryData( _rootItem );
}

pRecordDataModel::~pRecordDataModel() {
    delete _rootItem;
}

int pRecordDataModel::columnCount (const QModelIndex& parent) const {
    if( parent.isValid() )
        return 0;

    return _sortedParams.count();
}

int pRecordDataModel::rowCount (const QModelIndex& parent ) const {
    pRecTreeItem* pItem = getItem( parent );
    int nr = pItem->childCount();

    return nr;//_records.count();
}

QModelIndex pRecordDataModel::pRecordDataModel::index (int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() && parent.column() != 0 )
        return QModelIndex();

//    QMap<qint64, QSharedPointer< pRecordCopy > >::const_iterator prc = _records.constBegin()+row;
//    QSharedPointer< pRecordCopy > pRec = prc.value();
//    return createIndex( row, column, (void *)(pRec.get()));
    pRecTreeItem* parentItem = getItem( parent );

    pRecTreeItem* childItem = parentItem->child( row );
    if( childItem )
        return createIndex( row, column, childItem );
    else
        return QModelIndex();
}

QModelIndex pRecordDataModel::parent (const QModelIndex& index) const {
    if (!index.isValid())
        return QModelIndex();

    pRecTreeItem* childItem = getItem( index );
    pRecTreeItem* parentItem = childItem ? childItem->parent() : nullptr ;
    if( !parentItem || parentItem == _rootItem )
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}

Qt::ItemFlags pRecordDataModel::flags (const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if (index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    else
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant pRecordDataModel::data (const QModelIndex& index, int role) const {
    if( role == Qt::UserRole+2 )
        return QVariant::fromValue< QSharedPointer< const pCategory > >( _pCategory );
    else if( role == Qt::UserRole+3 )
        return QVariant::fromValue< QSharedPointer< const pCatParameter > >( _cParamParent );
    else if( role == Qt::UserRole+4 )
        return QVariant::fromValue< QSharedPointer< const pCatParameter > >( _cParamBackground );
    else if( role == Qt::UserRole+5 )
        return QVariant::fromValue< QSharedPointer< const pCatParameter > >( _cParamForeground );

    if (!index.isValid() )
        return QVariant();

    pRecTreeItem* wItem = static_cast< pRecTreeItem* >( index.internalPointer() );
    if( wItem == nullptr )
        return QVariant();
    //qDebug() << __PRETTY_FUNCTION__ << role << Qt::UserRole << Qt::BackgroundRole << Qt::ForegroundRole << Qt::DecorationRole;
    int iCol = index.column();
    qint64 idw = wItem->id();
    if( role == Qt::DisplayRole || role == Qt::ToolTipRole )
        return wItem->columnData( iCol );
    else if( role == Qt::UserRole )
        return idw;
    else if( role == Qt::UserRole+1 )
        return QVariant::fromValue< QSharedPointer< const pRecordCopy >>(wItem->getData());
    else if( role == Qt::BackgroundRole ) {
        if( wItem->getData().isNull() )
            return QVariant();
        QSharedPointer< const pRecordCopy > pRec = wItem->getData();
        QString pCode = _cParamBackground.isNull() ? QString("record_fill_color") :_cParamBackground->getCode();
        bool ok;
        QSharedPointer< const pParamValue > pVal = pRec->paramValue( pCode );
        if( pVal.isNull() )
            return QVariant();
        quint64 retVal = pVal->value().toULongLong( &ok );
        if( !ok )
            return QVariant();
        QVariant vc = QColor::fromRgba( retVal );
        return vc;
    }
    else if( role == Qt::ForegroundRole ) {
        if( wItem->getData().isNull() )
            return QVariant();
        QSharedPointer< const pRecordCopy > pRec = wItem->getData();
        QString pCode = _cParamForeground.isNull() ? QString("record_text_color") :_cParamBackground->getCode();
        bool ok;
        QSharedPointer< const pParamValue > pVal = pRec->paramValue( pCode );
        if( pVal.isNull() )
            return QVariant();
        quint64 retVal = pVal->value().toULongLong( &ok );
        if( !ok )
            return QVariant();
        QVariant vc = QColor::fromRgba( retVal );
        return vc;
    }
    else if( role == Qt::DecorationRole && index.column() == 0)
        return QIcon(":/patrol/view.png");
    return QVariant();
}

bool pRecordDataModel::setData (const QModelIndex& index, const QVariant& value, int role) {
    Q_UNUSED( index );
    Q_UNUSED( role );
    Q_UNUSED( value );
    return false;
}

QVariant pRecordDataModel::headerData (int section, Qt::Orientation orientation, int role) const {
    if( section < 0 || section >= _sortedParams.count() || orientation != Qt::Horizontal || (role != Qt::DisplayRole && role != Qt::EditRole) )
        return QVariant();

    QMap<int, QSharedPointer< const pCatParameter > >::const_iterator pp = _sortedParams.constBegin()+section;
    return pp.value()->getTitle();
}

bool pRecordDataModel::insertRows (int row, int count, const QModelIndex& parent ) {
    pRecTreeItem* pItem = getItem( parent );
    bool ok ( true );
    beginInsertRows( parent, row, row+count-1 );
    ok = pItem->insertChildren( row, count );

    endInsertRows();
    return ok;
}

bool pRecordDataModel::removeRows (int row, int count, const QModelIndex& parent ) {
    if( count== 0 )
        return true;

    pRecTreeItem* pItem = getItem( parent );
    bool ok ( true );
    beginRemoveRows( parent, row, row+count-1 );
    ok = pItem->removeChildren( row, count );
    endRemoveRows( );

    return ok;
}

void pRecordDataModel::setupParams() {
    if( _pCategory.isNull() )
        return;

    QMap< qint64, QSharedPointer< pCatParameter > > cpars = _pCategory->categoryPars();
    QList< QSharedPointer< pCatParameter > > wcpars = cpars.values();
    int n = wcpars.size();
    for(int i=0; i<n; i++) {
        if( wcpars[i]->getParamType()->getId() == pParamType::atRecordColor ||
            wcpars[i]->getParamType()->getId() == pParamType::atRecordColorRef ||
            wcpars[i]->getParamType()->getId() == pParamType::atRecordTextColor ||
            wcpars[i]->getParamType()->getId() == pParamType::atRecordTextColorRef )
            continue;
        _sortedParams.insert( wcpars[i]->getOrder(), wcpars[i] );
    }
}

QSharedPointer< const pCatParameter > pRecordDataModel::getFirstParameter( pParamType::PatrolParamTypes pType ) {
    if ( _pCategory.isNull() )
        return nullptr;

    QList< qint64 > paramListId = _pCategory->searchParametersByType( pType );
    if (paramListId.isEmpty() )
        return nullptr;

    qint64 pId = paramListId[0];
    QSharedPointer< const pCatParameter > param = _pCategory->categoryPars().value( pId );
    return param;
}

void pRecordDataModel::setupCategoryData(pRecTreeItem* parent) {
    if( _cParamParent.isNull() ) {
        for( QMap< qint64, QSharedPointer< pRecordCopy > >::const_iterator prec = _records.constBegin();
                prec != _records.constEnd();
                prec++ ) {
            QSharedPointer< const pParamValue > pVal = prec.value().isNull() ? nullptr : prec.value()->paramValue("r_icon");
            QString strIcon = pVal.isNull() ? QString() : pVal->value().toString();
            QIcon wIcon;
            if( !strIcon.isEmpty() ) {
                QPixmap pIcon;
                pIcon.loadFromData (strIcon.toUtf8());
                wIcon = pIcon;
            }
            pRecTreeItem* wItem = new pRecTreeItem( prec.key(), prec.value(), _sortedParams, wIcon );
            parent->appendChild( wItem );
        }
        return;
    }

    QModelIndex pIndex = QModelIndex ();
    pRecTreeItem* prevItem( nullptr );
    for( QMap< qint64, QSharedPointer< pRecordCopy > >::const_iterator prec = _records.constBegin();
            prec != _records.constEnd();
            prec++ ) {
        QIcon wIcon;
        if( !prec.value().isNull() ) {
            QSharedPointer< const pParamValue > pVal = prec.value()->paramValue("r_icon");
            QString strIcon = pVal.isNull() ? QString() : pVal->value().toString();
            QPixmap pIcon;
            pIcon.loadFromData( strIcon.toUtf8() );
            wIcon = QIcon( pIcon );
        }
        pRecTreeItem* t = new pRecTreeItem( prec.value()->paramValue("id")->value().toLongLong(), prec.value(), _sortedParams, wIcon );
        if( t->getData().isNull() )
            continue;

        QString valStr = prec.value()->paramValue( _cParamParent->getCode() )->value().toString();
        if( valStr.isEmpty() )
            parent->appendChild( t );
        else {
            bool ok;
            qint64 iVal = valStr.toLongLong( &ok );
            if( ok && iVal > 0 ) {
                if( prevItem && prevItem->id() == iVal )
                    prevItem->appendChild( t );
                else if( prevItem ) {
                    pRecTreeItem* p1( nullptr );
                    while( prevItem && prevItem->id() != iVal && p1 == nullptr ) {
                        prevItem = prevItem->parent();
                        p1 = getModelItem( iVal, prevItem, pIndex );
                    }
                    if( p1 == nullptr )
                        parent->appendChild( t );
                    else {
                        prevItem = p1;
                        prevItem->appendChild( t );
                    }
                }
                else {
                    pRecTreeItem* parent1 = getModelItem( iVal, _rootItem, pIndex );
                    if( parent1 == nullptr ) { //такая ситуация вообще-то является странной, признак того, что что-то не так
                        parent->appendChild( t );
                        prevItem = nullptr;
                    }
                    else {
                        parent1->appendChild( t );
                        prevItem = parent1;
                    }
                }
            }
            else {
                parent->appendChild( t );
                prevItem = nullptr;
            }
        }
    }
    return;
}

pRecTreeItem* pRecordDataModel::getModelItem (qint64 val, pRecTreeItem* parent, QModelIndex & pIndex) {
    if( parent == nullptr )
        return _rootItem;

    for( int i=0; i<parent->childCount(); i++) {
        pRecTreeItem* item = parent->child( i );
        //QString refCol = QString("id");//_cParamParent->getColumnName();
        //QString pStr = item->getData()->paramValue( refCol )->value().toString();
        //bool ok( true );
        qint64 iVal = item->id();
        if( iVal == val ) {
            pIndex = index( i, 0, pIndex );
            return item;
        }
        else if( item->childCount() > 0 ) {
            pRecTreeItem* chItem = getModelItem( val, item, pIndex );
            if( chItem )
                return chItem;
        }
    }

    return nullptr;
}

pRecTreeItem* pRecordDataModel::getItem(const QModelIndex &index) const {
    if( index.isValid() ) {
        pRecTreeItem* item = static_cast<pRecTreeItem*>( index.internalPointer() );
        if( item != nullptr )
            return item;
    }
    return _rootItem;
}
