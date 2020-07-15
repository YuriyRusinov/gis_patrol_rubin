/*
 * @brief Вспомогательный класс, содержащий группы записей в древовидной структуре
 * pRecTreeItem.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>

#include <pCatParameter.h>
#include <pRecordC.h>
#include <pParameter.h>
#include <pParamType.h>
#include <pParamValue.h>

#include "pRecTreeItem.h"

pRecTreeItem::pRecTreeItem(qint64 id, QSharedPointer<const pRecordCopy> pRec, const QMap< int, QSharedPointer< const pCatParameter > >& sortedParams, const QIcon& recIcon, pRecTreeItem* parent)
    : _id( id ),
    _sortedParameters( sortedParams ),
    _pRecord( pRec ),
    _itemIcon( recIcon ),
    _parentItem( parent ) {
        initData( _pRecord, _sortedParameters );
}

pRecTreeItem::~pRecTreeItem() {
    qDeleteAll (_childItems);
    if( !_pRecord.isNull() )
        _pRecord.reset();
}

pRecTreeItem* pRecTreeItem::child( int row ) {
    return _childItems.value( row );
}

int pRecTreeItem::childCount() const {
    return _childItems.count();
}

int pRecTreeItem::columnCount() const {
    return _itemData.count();
}

QSharedPointer<const pRecordCopy> pRecTreeItem::getData() const {
    return _pRecord;
}

QVariant pRecTreeItem::columnData( int column ) {
    if( column >= 0 && column < _itemData.count() )
        return _itemData[ column ];

    return QVariant();
}

void pRecTreeItem::setData( QSharedPointer<const pRecordCopy> pRec, const QMap< int, QSharedPointer< const pCatParameter > >& sortedParams ) {
    if (pRec == _pRecord)
        return;
    _pRecord = pRec;
    _sortedParameters = sortedParams;

    initData( _pRecord, _sortedParameters );
}

bool pRecTreeItem::setData( int column, const QVariant& value ) {
    if (column < 0 || column >= _itemData.size())
        return false;

     _itemData[column] = value;
     return true;
}

bool pRecTreeItem::insertChildren( int position, int count ) {
    if (position < 0 || position > _childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
    {
         QSharedPointer< const pRecordCopy > d ( nullptr );//data;
         QIcon ic;
         pRecTreeItem *item = new pRecTreeItem(-1-row, d, _sortedParameters, ic, this);
         _childItems.insert(position, item);
     }

     return true;
}

pRecTreeItem* pRecTreeItem::parent() {
    return _parentItem;
}

bool pRecTreeItem::removeChildren( int position, int count ) {
    if (position < 0 || position + count > _childItems.size())
        return false;
    
    for (int row=0; row<count; ++row)
    {
        delete _childItems.takeAt(position);
    }
    
    return true;
}

int pRecTreeItem::childNumber() const {
    if( _parentItem != nullptr )
        return _parentItem->_childItems.indexOf( const_cast< pRecTreeItem*>(this) );

    return 0;
}

void pRecTreeItem::appendChild( pRecTreeItem* child ) {
    if ( child == nullptr )
        return;

    child->setParent( this );
    QSharedPointer< const pRecordCopy > prec = child->_pRecord;
    _childItems.append( child );
    child->initData( prec, _sortedParameters );
}

void pRecTreeItem::setParent( pRecTreeItem* p ) {
    if( _parentItem != nullptr && _parentItem != p )
        delete _parentItem;

    _parentItem = p;
}

qint64 pRecTreeItem::id() const {
    return _id;
}

void pRecTreeItem::setId( qint64 newId ) {
    _id = newId;
}

void pRecTreeItem::clearChildren() {
    qDeleteAll (_childItems);
    _childItems.clear ();
}

QIcon pRecTreeItem::getIcon() const {
    return _itemIcon;
}

void pRecTreeItem::setIcon( const QIcon& icon ) {
    _itemIcon = icon;
}

void pRecTreeItem::initData( QSharedPointer< const pRecordCopy > pRec, const QMap< int, QSharedPointer< const pCatParameter > >& sortedParams ) {
    if( pRec.isNull() || sortedParams.isEmpty() )
        return;

    _itemData.clear();
    int iNum = this->childNumber() + 1;
    int na = sortedParams.size();
    Q_UNUSED( na );
    for( QMap< int, QSharedPointer< const pCatParameter > >::const_iterator pa = sortedParams.constBegin();
            pa != sortedParams.constEnd();
            pa++ ) {
        QSharedPointer< const pCatParameter > v = pa.value();
        //qDebug() << __PRETTY_FUNCTION__ << pa.value()->getCode();
        QString pValue;
        if( v->getParamType()->getId() == pParamType::atCheckListEx ) {
            pValue = QObject::tr("<Set of references %1, dbl-click for details and see result table>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atImage ||
                 ( !v->getRefParamType().isNull() && v->getRefParamType()->getId() == pParamType::atImage )) {
            pValue = QObject::tr("<Image data %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atSVG || 
                (!v->getRefParamType().isNull() && v->getRefParamType()->getId() == pParamType::atSVG) ) {
            pValue = QObject::tr("<SVG data %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atXML ||
                (!v->getRefParamType().isNull() && v->getRefParamType()->getId() == pParamType::atXML )) {
            pValue = QObject::tr("<XML document %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atVideo ||
              (!v->getRefParamType().isNull() && v->getRefParamType()->getId() == pParamType::atVideo) ) {
            pValue = QObject::tr("<Video data %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atGeometry ||
                 v->getParamType()->getId() == pParamType::atGeography ||
                 v->getParamType()->getId() == pParamType::atGISMap ||
                 (!v->getRefParamType().isNull() && ( v->getRefParamType()->getId() == pParamType::atGeometry || v->getRefParamType()->getId() == pParamType::atGeography || v->getRefParamType()->getId() == pParamType::pParamType::atGISMap))
               ) {
            pValue = QObject::tr("<Geometry data %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atComplex ||
              (!v->getRefParamType().isNull() && v->getRefParamType()->getId() == pParamType::atComplex) ) {
            pValue = QObject::tr("<Complex value %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atJSON ||
                 v->getParamType()->getId() == pParamType::atJSONb ||
                 (!v->getRefParamType().isNull() && (v->getRefParamType()->getId() == pParamType::atJSON || v->getRefParamType()->getId() == pParamType::atJSONb ))
               ) {
            pValue = QObject::tr("<json value %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atBinary ||
               (!v->getRefParamType().isNull() && v->getRefParamType()->getId() == pParamType::atBinary ) ) {
            pValue = QObject::tr("<Binary data %1>").arg( iNum );
        }
        else if( v->getParamType()->getId() == pParamType::atList ||
                 v->getParamType()->getId() == pParamType::atParent ) {
            QString pCode = v->getCode();
            pValue = pRec->paramValue( pCode )->getColumnValue();
        }
        else {
            QString pCode = v->getCode();
            pValue = pRec->paramValue( pCode )->value().toString();//getColumnValue();
            //qDebug() << __PRETTY_FUNCTION__ << pCode << pValue;
            if( pValue.contains ("\n") )
                pValue = pValue.mid( 0, pValue.indexOf("\n")) + "...";
        }
        _itemData.append( QVariant( pValue ) );
    }
}
