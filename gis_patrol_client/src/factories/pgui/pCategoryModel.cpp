/*
 * @brief Класс, описывающий визуальную модель категорий
 * pCategoryModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <pCategory.h>
#include <pCategoryType.h>
#include "pCatTreeItem.h"
#include "pCategoryModel.h"

pCategoryModel::pCategoryModel( const QMap< qint64, QSharedPointer< pCategory > >& categories, QObject* parent )
    : QAbstractItemModel( parent ),
    _categories( categories ),
    _rootItem( new pCatTreeItem ) {
    setupModel( _categories, _rootItem );
}

pCategoryModel::~pCategoryModel( ) {
}

Qt::ItemFlags pCategoryModel::flags(const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool pCategoryModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    Q_UNUSED( index );
    Q_UNUSED( value );
    Q_UNUSED( role );
    return false;
}

int pCategoryModel::columnCount( const QModelIndex& parent ) const {
    Q_UNUSED( parent );
    return 4;
}

int pCategoryModel::rowCount( const QModelIndex& parent ) const {
    pCatTreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<pCatTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

QModelIndex pCategoryModel::index(int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() && parent.column() != 0 )
        return QModelIndex();

    pCatTreeItem* parentItem = getItem ( parent );
    if( !parentItem )
        return QModelIndex();

    pCatTreeItem* childItem = parentItem->child( row );
    if( childItem )
        return createIndex( row, column, childItem );

    return QModelIndex();

/*     if (pCat == nullptr && !parent.isValid()) {
        pCat = new pCategory (*((_categories.constBegin()+row).value().get()));
        return createIndex(row, column, pCat);
    }
    else
        return QModelIndex();

    if( !pCat->getTableCat().isNull() ) {
        qDebug() << __PRETTY_FUNCTION__ << QString("Child category");
        return createIndex(row, column, pCat->getTableCat().get() );
    }
        int prow = parent.row();
        QMap<qint64, QSharedPointer< pCategory > >::const_iterator pcat = _categories.constBegin()+prow;
        if( !pcat.value()->getTableCat().isNull() ) {
            return QModelIndex();//createIndex(row, column, pcat.value()->getTableCat().get());
        }
        else
            return QModelIndex();
    }
    else if ( !parent.isValid() ) {
        QMap<qint64, QSharedPointer< pCategory > >::const_iterator pcat = _categories.constBegin()+row;
        return createIndex(row, column, pcat.value().get() );
    }
*/
}

QModelIndex pCategoryModel::parent(const QModelIndex& index) const {
    if (!index.isValid())
        return QModelIndex();

    pCatTreeItem *childItem = getItem( index );
    //static_cast<pTreeItem*>(index.internalPointer());
    pCatTreeItem *parentItem = childItem ? childItem->parentItem() : nullptr;

    if (!parentItem || parentItem == _rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
/*
//    int irow = index.row();
    pCategory* pcat = (pCategory *)(index.internalPointer());
    if (!pcat)
        return QModelIndex();
    qint64 idCat = pcat->getId();
    QMap<qint64, QSharedPointer< pCategory > >::const_iterator pcc = _categories.constFind( idCat );
    if (pcc != _categories.constEnd())
        return QModelIndex();
    
    bool isChildFind = false;
    int nchild = 0;
    for (QMap<qint64, QSharedPointer< pCategory > >::const_iterator pcc = _categories.constBegin(); pcc != _categories.constEnd() && !isChildFind; pcc++) {
        isChildFind = (pcc.value()->getTableCat()->getId() == idCat);
        if( !isChildFind )
            nchild++;
    }
    if (isChildFind)
        return createIndex(nchild, 0, (_categories.constBegin()+nchild).value().get());
    else
        return QModelIndex();
*/
    Q_UNUSED( index );
    return QModelIndex();
}

QVariant pCategoryModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() )
        return QVariant();

    pCatTreeItem* wItem = static_cast< pCatTreeItem* >( index.internalPointer() );
    QSharedPointer< pCategory > pCat = wItem->getCategory();
    if (!pCat)
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch( index.column() ) {
          case 0: return pCat->getName(); break;
          case 1: return pCat->getCode(); break;
          case 2: return pCat->getDesc(); break;
          case 3: return pCat->getType()->getName(); break;
          default: return QVariant(); break;
        }
    }
    else if (role == Qt::UserRole) {
        return pCat->getId();
    }
    else if (role == Qt::UserRole+1) {
        return QVariant::fromValue< QSharedPointer< pCategory > >( pCat );
    }
    return QVariant();
}

QVariant pCategoryModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QStringList headers;
    headers << tr("Name") << tr("Code") << tr("Description") << tr("Name of type");
    if(section >= 0 && section < 4 && orientation == Qt::Horizontal && role == Qt::DisplayRole)
      return headers[section];

    return QVariant();
}

bool pCategoryModel::insertRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED( position );
    Q_UNUSED( rows );
    Q_UNUSED( parent );
    return false;
}

bool pCategoryModel::removeRows(int position, int rows, const QModelIndex &parent) {
    Q_UNUSED( position );
    Q_UNUSED( rows );
    Q_UNUSED( parent );
    return false;
}

pCatTreeItem* pCategoryModel::getItem(QModelIndex index) const {
    if (index.isValid()) {
        pCatTreeItem *item = static_cast<pCatTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return _rootItem;
}

void pCategoryModel::setupModel( const QMap< qint64, QSharedPointer< pCategory > >& cats, pCatTreeItem* rootItem ) {
  QVector< pCatTreeItem* > parents;
  parents << rootItem;
  for( QMap< qint64, QSharedPointer< pCategory > >::const_iterator pc = cats.constBegin();
      pc != cats.constEnd();
      pc++) {
    pCatTreeItem* ptr = new pCatTreeItem( pc.value(), parents.last() );
    QSharedPointer< pCategory > pcat = ptr->getCategory();
    if( !pcat->getTableCat().isNull() ) {
        pCatTreeItem* pctr = new pCatTreeItem( pcat->getTableCat(), ptr );
        ptr->appendChild( pctr );
    }
    parents.last()->appendChild( ptr );
  }
}
