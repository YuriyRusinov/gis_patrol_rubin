/*
 * @brief Вспомогательный класс, содержащий категории и дочерние категории в древовидной структуре
 * pCatTreeItem.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QVariant>
#include <QVector>
#include <QSharedPointer>

class pCategory;

class pCatTreeItem {
public:
    explicit pCatTreeItem( QSharedPointer< pCategory > pcat=nullptr, pCatTreeItem* parent=nullptr );
    ~pCatTreeItem();

    void appendChild( pCatTreeItem* child );

    pCatTreeItem* child(int row);

    int childCount() const;
    int columnCount() const;

    QVariant data(int column) const;
    bool insertChildren(int position, int count);
    bool removeChildren(int position, int count);
    int row() const;
    pCatTreeItem *parentItem();

    QSharedPointer< pCategory > getCategory() const;
    void setCategory( QSharedPointer< pCategory > pCat );

private:
    QVector< pCatTreeItem* > _childItems;
    QSharedPointer< pCategory > _pCategory;
    pCatTreeItem* _parentItem;
};
