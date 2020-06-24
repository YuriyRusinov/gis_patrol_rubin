/*
 * @brief Вспомогательный класс, содержащий категории и дочерние категории в древовидной структуре
 * pCatTreeItem.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <pCategory.h>
#include <pCategoryType.h>
#include "pCatTreeItem.h"

pCatTreeItem::pCatTreeItem( QSharedPointer< pCategory > pgr, pCatTreeItem* parent )
    : _pCategory ( pgr ), _parentItem( parent ) {
    _childItems.clear();
}

pCatTreeItem::~pCatTreeItem() {
    qDeleteAll(_childItems);
}

void pCatTreeItem::appendChild( pCatTreeItem* child ) {
    _childItems.append( child );
}

pCatTreeItem* pCatTreeItem::child( int row ) {
    if ( row < 0 || row >= _childItems.size() )
        return nullptr;

    return _childItems[row];
}

int pCatTreeItem::childCount() const {
    return _childItems.size();
}

int pCatTreeItem::columnCount() const {
    return 4;
}

QVariant pCatTreeItem::data(int column) const {
    switch (column) {
        case 0: return _pCategory->getName(); break;
        case 1: return _pCategory->getCode(); break;
        case 2: return _pCategory->getDesc(); break;
        case 3: return _pCategory->getType()->getName(); break;
        default: return QVariant(); break;
    }
    return QVariant();
}

int pCatTreeItem::row() const {
    if (_parentItem) {
        return _parentItem->_childItems.indexOf(const_cast<pCatTreeItem*>(this));
    }

    return 0;
}

pCatTreeItem* pCatTreeItem::parentItem() {
    return _parentItem;
}

bool pCatTreeItem::insertChildren(int position, int count) {

    if (position < 0 || position > _childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        pCatTreeItem *item = new pCatTreeItem(QSharedPointer< pCategory >(nullptr), this);
        _childItems.insert(position, item);
    }

    return true;
}

bool pCatTreeItem::removeChildren(int position, int count) {
    if (position < 0 || position + count > _childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete _childItems.takeAt(position);

    return true;
}

QSharedPointer< pCategory > pCatTreeItem::getCategory() const {
  return _pCategory;
}

void pCatTreeItem::setCategory( QSharedPointer< pCategory > pCat ) {
  _pCategory = pCat;
}
