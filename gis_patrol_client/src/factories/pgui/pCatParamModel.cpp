/*
 * @brief Класс, описывающий визуальную модель параметров, сгруппированных по подходящим пользовательским группам
 * pParamModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <defines.h>
#include <QtDebug>
#include <pCatParameter.h>
#include "pCatParamModel.h"

pCatParametersModel::pCatParametersModel( const QMap< qint64, QSharedPointer< pCatParameter > >& paramGroups, QObject* parent )
    : QAbstractItemModel( parent ), _pCategoryParams(paramGroups) {
//      , _pCatParams( paramGroups.values() ) {
    qDebug() << __PRETTY_FUNCTION__;
}

pCatParametersModel::~pCatParametersModel() {
}

int pCatParametersModel::columnCount( const QModelIndex& parent) const {
    Q_UNUSED( parent );
    return 5;
}

int pCatParametersModel::rowCount( const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;

    return _pCategoryParams.size();
}

QModelIndex pCatParametersModel::index(int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() )
        return QModelIndex();

    if (row >= 0 && row < _pCategoryParams.size() ) {
        QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _pCategoryParams.constBegin()+row;
        return createIndex(row, column, pct->get() );
    }
    return QModelIndex();
}

QModelIndex pCatParametersModel::parent(const QModelIndex& index) const {
    Q_UNUSED( index );
    return QModelIndex();
}

QVariant pCatParametersModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    int iRow = index.row();
    int iColumn = index.column();
    QList< qint64 > catParKeys = _pCategoryParams.keys();
/*
 *  Отладочная печать приоритетов
    int nc = catParKeys.size();
    for (int i=0; i<nc; i++) {
        QSharedPointer< pCatParameter > wpc = _pCategoryParams.value ( catParKeys[i] );
        if (wpc.isNull() )
            continue;
        qDebug() << __PRETTY_FUNCTION__ << wpc->getOrder();
    }
*/
    QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _pCategoryParams.constFind( catParKeys[iRow] );
    if( role == Qt::UserRole ) {
        return pct.key();
    }
    else if ( role == Qt::UserRole+1 ) {
        return (pct.key() <= 0 || pct.value().isNull()) ? QVariant() : QVariant::fromValue< QSharedPointer< pCatParameter > >(pct.value());
    }
    else if ( role == Qt::UserRole+2 ) {
        return (pct.key() <= 0 || pct.value().isNull()) ? QVariant() : QVariant(pct.value()->getOrder());
    }
    else if (role == Qt::DisplayRole) {
        if (pct.key() <= 0 || pct.value().isNull())
            return QVariant();
        switch( iColumn ) {
            case 0: return pct.value()->getName(); break;
            case 1: return pct.value()->getDefaultValue(); break;
            case 4: return pct.value()->getOrder(); break;
            default: return QVariant(); break;
        }
    }
    else if (role == Qt::CheckStateRole) {
        if (pct.key() <= 0 || pct.value().isNull())
            return QVariant();
        switch( iColumn ) {
            case 2: return (pct.value()->isMandatory() ? Qt::Checked : Qt::Unchecked); break;
            case 3: return (pct.value()->isReadOnly() ? Qt::Checked : Qt::Unchecked); break;
            default: return QVariant(); break;
        }
    }

    return QVariant();
}

QVariant pCatParametersModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QStringList headers;
    headers << tr( "Name" ) << tr("Default Value") << tr( "Mandatory" ) << tr( "Read only" ) << tr( "Order" );
    if (section >= 0 && section < headers.size() && orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers[section];

    return QVariant();
}

Qt::ItemFlags pCatParametersModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool pCatParametersModel::setData(const QModelIndex& index, const QVariant &value,
             int role) {
    if (!index.isValid())
        return false;

    int iRow = index.row();
    if (iRow > _pCategoryParams.size())
        return false;
    QList< qint64 > ckeys = _pCategoryParams.keys();
    if( role == Qt::UserRole+1 ) {
        QSharedPointer< pCatParameter > pgr = value.value< QSharedPointer< pCatParameter >>();
        qint64 newKey = pgr->getId();
        QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _pCategoryParams.constFind( newKey );
        qint64 oldKey = (pct == _pCategoryParams.constEnd() ? _pCategoryParams.firstKey() : pct.key());
        qDebug() << __PRETTY_FUNCTION__ << newKey << oldKey;
        if( oldKey < 0 )//!= newKey )
            _pCategoryParams.remove( oldKey );
        _pCategoryParams.insert( newKey, pgr );
        emit dataChanged( index.sibling(iRow, 0), index.sibling(iRow, 4), {Qt::DisplayRole, Qt::EditRole, Qt::UserRole, Qt::UserRole+1});
        return true;
    }
    else if ( role == Qt::UserRole+2 ) {
        qint64 wKey = ckeys[ index.row() ];
        QSharedPointer< pCatParameter > pgr = _pCategoryParams.value( wKey );
        if( pgr.isNull() )
            return false;
        pgr->setOrder( value.toInt() );
        emit dataChanged( index, index, {Qt::EditRole, Qt::UserRole+1, Qt::UserRole+2});
    }
    else if( index.column()==1 && (role == Qt::DisplayRole || role== Qt::EditRole) ) {
        qint64 wKey = ckeys[ index.row() ];
        QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _pCategoryParams.constFind( wKey );
        pct.value()->setDefaultValue( value );
        emit dataChanged( index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    else if( index.column() == 2 && role == Qt::CheckStateRole ) {
        qint64 wKey = ckeys[ index.row() ];
        QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _pCategoryParams.constFind( wKey );
        pct.value()->setMandatory( (value==Qt::Checked) );
        emit dataChanged( index, index, {Qt::CheckStateRole} );
        return true;
    }
    else if( index.column() == 3 && role == Qt::CheckStateRole ) {
        qint64 wKey = ckeys[ index.row() ];
        QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pct = _pCategoryParams.constFind( wKey );
        pct.value()->setReadOnly( (value==Qt::Checked) );
        emit dataChanged( index, index, {Qt::CheckStateRole} );
        return true;
    }
    return false;
}

bool pCatParametersModel::insertRows(int position, int rows, const QModelIndex &parent) {
    if (parent.isValid() || position < 0 || position > _pCategoryParams.size())
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    QMap< qint64, QSharedPointer< pCatParameter > >::iterator pos = _pCategoryParams.begin();
    qint64 cFirstKey = -1;
    if( !_pCategoryParams.isEmpty() && _pCategoryParams.firstKey() < 0)
        cFirstKey = _pCategoryParams.firstKey()-1;
    for (int i=0; i<rows; i++) {
        pos = _pCategoryParams.insert( cFirstKey-i, QSharedPointer< pCatParameter >(nullptr)) ;
    }
    const bool success = (pos != _pCategoryParams.end() );
    //parentItem->insertChildren(position,                                              rows);
    endInsertRows();
//    qDebug() << __PRETTY_FUNCTION__ << _pCategoryParams.keys() << success;
    return success;
}

bool pCatParametersModel::removeRows(int position, int rows, const QModelIndex &parent) {
    if (parent.isValid() || position < 0 || position+rows-1 >= _pCategoryParams.size())
        return false;

    QList< qint64 > catParKeys = _pCategoryParams.keys();
    beginRemoveRows(parent, position, position + rows - 1);
    for (int i=0; i<rows; i++) {
        _pCategoryParams.remove( catParKeys[position+i] );
    }
    int nRemainSize = catParKeys.size() - (position + rows - 1);
    if (nRemainSize > 0) {
        for (int i=position+rows; i < catParKeys.size(); i++) {
            QSharedPointer< pCatParameter > pc = _pCategoryParams.value( catParKeys[i], nullptr );
            if ( pc.isNull() )
                continue;
            int pco = pc->getOrder();
            pc->setOrder( pco-rows );
        }
    }
    const bool success = true;
    endRemoveRows();

    return success;
}
