/*
 * @brief Вспомогательный класс, содержащий группы параметров в древовидной структуре
 * pTreeItem.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QVariant>
#include <QVector>
#include <QSharedPointer>

class pParamGroup;
class pParameter;

class pTreeItem {
public:
    explicit pTreeItem( QSharedPointer< pParamGroup > pgr=nullptr, pTreeItem* parent=nullptr );
    explicit pTreeItem( QSharedPointer< pParameter > param, pTreeItem* parent=nullptr );
    ~pTreeItem();

    void appendChild( pTreeItem* child );

    pTreeItem* child(int row);

    bool isGroup() const;
    bool isParameter() const;

    int childCount() const;
    int columnCount() const;

    QVariant data(int column) const;
    bool insertChildren(int position, int count);
    bool removeChildren(int position, int count);
    int row() const;
    pTreeItem *parentItem();

    QSharedPointer< pParamGroup > getGroup() const;
    void setGroup( QSharedPointer< pParamGroup > group );
    QSharedPointer< pParameter > getParameter() const;
    void setParameter( QSharedPointer< pParameter > parameter );

private:
    QVector< pTreeItem* > _childItems;
    QSharedPointer< pParamGroup > _pGroup;
    QSharedPointer< pParameter > _pParam;
    pTreeItem* _parentItem;
};
