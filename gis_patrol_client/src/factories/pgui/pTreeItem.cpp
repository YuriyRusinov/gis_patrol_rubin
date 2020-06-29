/*
 * @brief Вспомогательный класс, содержащий группы параметров в древовидной структуре
 * pTreeItem.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>
#include <pParamGroup.h>
#include <pParameter.h>
#include <pParamType.h>
#include <pAttribute.h>
#include "pTreeItem.h"

pTreeItem::pTreeItem( QSharedPointer< pAttribute > pgr, pTreeItem* parent )
    : _pAttr ( pgr ), _parentItem( parent ) {
    _childItems.clear();
}

pTreeItem::~pTreeItem() {
    qDeleteAll(_childItems);
}

void pTreeItem::appendChild( pTreeItem* child ) {
    _childItems.append( child );
}

pTreeItem* pTreeItem::child( int row ) {
    if ( row < 0 || row >= _childItems.size() )
        return nullptr;

    return _childItems[row];
}

int pTreeItem::getEntity() const {
    if (_pAttr.isNull())
        return -1;

    return _pAttr->getEntity();
}

qint64 pTreeItem::getId() const {
    if (_pAttr.isNull())
        return -1;

    return _pAttr->getId();
}

bool pTreeItem::isNull() const {
    return _pAttr.isNull();
}

int pTreeItem::childCount() const {
    return _childItems.size();
}

int pTreeItem::columnCount() const {
    return 7;
}

QVariant pTreeItem::data(int column) const {
    if (_pAttr.isNull())
        return QVariant();
    else if ( _pAttr->getEntity() == 0  && column >=0 && column < 1) {
        QSharedPointer< pParamGroup > _pGroup = qSharedPointerDynamicCast< pParamGroup >(_pAttr );
        return _pGroup->getName();
    }
    else if (_pAttr->getEntity() == 1) {
        QSharedPointer< pParameter > _pParam = qSharedPointerDynamicCast< pParameter >(_pAttr);
        switch (column) {
            case 0: return _pParam->getId(); break;
            case 1: return _pParam->getCode(); break;
            case 2: return _pParam->getName(); break;
            case 3: return _pParam->getTitle(); break;
            case 4: return _pParam->getTableName(); break;
            case 5: return _pParam->getColumnName(); break;
            case 6: return _pParam->getParamType()->getCode(); break;
            default: return QString(); break;
        }
    }
    return QVariant();
}

int pTreeItem::row() const {
    if (_parentItem) {
        return _parentItem->_childItems.indexOf(const_cast<pTreeItem*>(this));
    }

    return 0;
}

pTreeItem* pTreeItem::parentItem() {
    return _parentItem;
}

QSharedPointer< pParamGroup > pTreeItem::getGroup() const {
    return qSharedPointerDynamicCast< pParamGroup >(_pAttr );
}

QSharedPointer< pParameter > pTreeItem::getParameter() const {
    return qSharedPointerDynamicCast< pParameter >(_pAttr);
}

bool pTreeItem::insertChildren(int position, int count) {

    if (position < 0 || position > _childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        pTreeItem *item = new pTreeItem(QSharedPointer< pAttribute >(nullptr), this);
        _childItems.insert(position, item);
    }

    return true;
}

bool pTreeItem::removeChildren(int position, int count) {
    if (position < 0 || position + count > _childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete _childItems.takeAt(position);

    return true;
}

void pTreeItem::setGroup( QSharedPointer< pParamGroup > group ) {
    _pAttr = group;
}

void pTreeItem::setParameter( QSharedPointer< pParameter > parameter ) {
    _pAttr = parameter;
}
