/*
 * @brief Вспомогательный класс, содержащий группы записей в древовидной структуре
 * pRecTreeItem.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QIcon>
#include <QMap>
#include <QSharedPointer>
#include <QVariant>
#include <QVector>

class pCatParameter;
class pRecordCopy;

class pRecTreeItem {
public:
    explicit pRecTreeItem(qint64 id, QSharedPointer<const pRecordCopy> pRec, const QMap< int, QSharedPointer< const pCatParameter > >& sortedParams, const QIcon& recIcon=QIcon(), pRecTreeItem* parent = nullptr );
    ~pRecTreeItem();

    pRecTreeItem* child( int row );
    int childCount() const;
    int columnCount() const;
    QSharedPointer<const pRecordCopy> getData() const;
    QVariant columnData( int column );
    void setData( QSharedPointer<const pRecordCopy> pRec, const QMap< int, QSharedPointer< const pCatParameter > >& sortedParams );
    bool setData( int column, const QVariant& value );
    bool insertChildren( int position, int count );
    pRecTreeItem* parent();
    bool removeChildren( int position, int count );
    int childNumber() const;
    void appendChild( pRecTreeItem* child );
    void setParent( pRecTreeItem* p );
    qint64 id() const;
    void setId( qint64 newId );
    void clearChildren();
    QIcon getIcon() const;
    void setIcon( const QIcon& icon );

    const QVector< QVariant >& getItemData () const { return _itemData ; }

private:
    //
    // Functions
    //
    void initData( QSharedPointer< const pRecordCopy > pRec, const QMap< int, QSharedPointer< const pCatParameter > >& sortedParams );
    pRecTreeItem() = delete;
    pRecTreeItem( const pRecTreeItem& ) = delete;
    pRecTreeItem& operator=( const pRecTreeItem& ) = delete;

private:
    //
    // Variables
    //
    qint64 _id;
    QMap< int, QSharedPointer< const pCatParameter > > _sortedParameters;
    QSharedPointer< const pRecordCopy > _pRecord;
    QIcon _itemIcon;
    QVector< QVariant > _itemData;
    pRecTreeItem* _parentItem;
    QList< pRecTreeItem* > _childItems;
};
