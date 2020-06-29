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
class pAttribute;

class pTreeItem {
public:
    explicit pTreeItem( QSharedPointer< pAttribute > pgr=nullptr, pTreeItem* parent=nullptr );
    ~pTreeItem();

    void appendChild( pTreeItem* child );

    pTreeItem* child(int row);

    bool isNull() const;
    int getEntity() const;
    qint64 getId() const;

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
    QSharedPointer< pAttribute > _pAttr;
    pTreeItem* _parentItem;
};
