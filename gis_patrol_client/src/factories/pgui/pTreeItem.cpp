/*
 * @brief Вспомогательный класс, содержащий группы параметров в древовидной структуре
 * pTreeItem.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <pParamGroup.h>
#include <pParameter.h>
#include <pParamType.h>
#include "pTreeItem.h"

pTreeItem::pTreeItem( QSharedPointer< pParamGroup > pgr, pTreeItem* parent )
    : _pGroup ( pgr ), _pParam( nullptr ), _parentItem( parent ) {
    _childItems.clear();
}

pTreeItem::pTreeItem( QSharedPointer< pParameter > param, pTreeItem* parent )
    : _pGroup( nullptr ), _pParam( param ), _parentItem( parent ) {
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

bool pTreeItem::isGroup() const {
    return !_pGroup.isNull();
}

bool pTreeItem::isParameter() const {
    return !_pParam.isNull();
}

int pTreeItem::childCount() const {
    return _childItems.size();
}

int pTreeItem::columnCount() const {
    return 7;
}

QVariant pTreeItem::data(int column) const {
    if (isGroup() && column >=0 && column < 1)
        return _pGroup->getName();
    else if (isParameter()) {
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
    return _pGroup;
}

QSharedPointer< pParameter > pTreeItem::getParameter() const {
    return _pParam;
}

bool pTreeItem::insertChildren(int position, int count) {

    if (position < 0 || position > _childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        pTreeItem *item = new pTreeItem(QSharedPointer< pParamGroup >(nullptr), this);
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
    _pGroup.reset();
    _pGroup = group;
    _pParam.reset();
}

void pTreeItem::setParameter( QSharedPointer< pParameter > parameter ) {
    _pGroup.reset();
    _pParam.reset();
    _pParam = parameter;
}
