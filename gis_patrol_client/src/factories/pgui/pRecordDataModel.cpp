/* 
 * @brief Класс описывает визуальную модель отображения данных
 * pRecordDataModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QModelIndex>
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
    if( parent.isValid() )
        return 0;

    return _records.count();
}

QModelIndex pRecordDataModel::pRecordDataModel::index (int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() || row >= _records.count() )
        return QModelIndex();

    QMap<qint64, QSharedPointer< pRecordCopy > >::const_iterator prc = _records.constBegin()+row;
    QSharedPointer< pRecordCopy > pRec = prc.value();
    return createIndex( row, column, (void *)(pRec.get()));
}

QModelIndex pRecordDataModel::parent (const QModelIndex& index) const {
    Q_UNUSED( index );
    return QModelIndex();
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
    if (!index.isValid() )
        return QVariant();
    Q_UNUSED( role );
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
    Q_UNUSED( row );
    Q_UNUSED( count );
    Q_UNUSED( parent );
    return false;
}

bool pRecordDataModel::removeRows (int row, int count, const QModelIndex& parent ) {
    Q_UNUSED( row );
    Q_UNUSED( count );
    Q_UNUSED( parent );
    return false;
}

void pRecordDataModel::setupParams() {
    if( _pCategory.isNull() )
        return;

    QMap< qint64, QSharedPointer< pCatParameter > > cpars = _pCategory->categoryPars();
    QList< QSharedPointer< pCatParameter > > wcpars = cpars.values();
    int n = wcpars.size();
    for(int i=0; i<n; i++) {
/*        if( wcpars[i]->getParamType()->getId() == pParamType::atImage ||
            wcpars[i]->getParamType()->getId() == pParamType::atCheckListEx ||
            wcpars[i]->getParamType()->getId() == pParamType::atRecordColor ||
            wcpars[i]->getParamType()->getId() == pParamType::atRecordColorRef ||
            wcpars[i]->getParamType()->getId() == pParamType::atXML ||
            wcpars[i]->getParamType()->getId() == pParamType::atSVG ||
            wcpars[i]->getParamType()->getId() == pParamType::atVideo ||
            wcpars[i]->getParamType()->getId() == pParamType::atRecordTextColor ||
            wcpars[i]->getParamType()->getId() == pParamType::atRecordTextColorRef ||
            wcpars[i]->getParamType()->getId() == pParamType::atGeometry ||
            wcpars[i]->getParamType()->getId() == pParamType::atGeography ||
            wcpars[i]->getParamType()->getId() == pParamType::atHistogram ||
            wcpars[i]->getParamType()->getId() == pParamType::atGISMap ||
            wcpars[i]->getParamType()->getId() == pParamType::atJSON ||
            wcpars[i]->getParamType()->getId() == pParamType::atJSONb ||
            wcpars[i]->getParamType()->getId() == pParamType::atBinary )
            continue;*/
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
    Q_UNUSED( parent );
}

pRecTreeItem* pRecordDataModel::getModelItem (qint64 val, pRecTreeItem* parent, QModelIndex & pIndex) {
    Q_UNUSED( val );
    Q_UNUSED( pIndex );
    if( parent == nullptr )
        return _rootItem;

    for( int i=0; i<parent->childCount(); i++) {
        pRecTreeItem* item = parent->child( i );
        QString refCol =_cParamParent->getColumnName();
        Q_UNUSED( item );
        Q_UNUSED( refCol );
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
