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
    : QAbstractItemModel( parent ), _pCatParams( paramGroups.values() ) {
    qDebug() << __PRETTY_FUNCTION__;
}

pCatParametersModel::~pCatParametersModel() {
}

int pCatParametersModel::columnCount( const QModelIndex& parent) const {
    Q_UNUSED( parent );
    return 4;
}

int pCatParametersModel::rowCount( const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;

    return _pCatParams.size();
}

QModelIndex pCatParametersModel::index(int row, int column, const QModelIndex& parent) const {
    if( parent.isValid() )
        return QModelIndex();

    if (row >= 0 && row < _pCatParams.size() ) {
        QList< QSharedPointer< pCatParameter > >::const_iterator pct = _pCatParams.constBegin()+row;
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
    QList< QSharedPointer< pCatParameter > >::const_iterator pct = _pCatParams.constBegin()+iRow;
    if( role == Qt::UserRole ) {
        return pct->isNull() ? -1 : (*pct)->getId();
    }
    else if ( role == Qt::UserRole+1 ) {
        return pct->isNull() ? QVariant() : QVariant::fromValue< QSharedPointer< pCatParameter > >(*pct);
    }
    else if (role == Qt::DisplayRole) {
        if (pct->isNull())
            return QVariant();
        switch( iColumn ) {
            case 0: return (*pct)->getName(); break;
            case 1: return (*pct)->getDefaultValue(); break;
            default: return QVariant(); break;
        }
    }
    else if (role == Qt::CheckStateRole) {
        if (pct->isNull())
            return QVariant();
        switch( iColumn ) {
            case 2: return ((*pct)->isMandatory() ? Qt::Checked : Qt::Unchecked); break;
            case 3: return ((*pct)->isReadOnly() ? Qt::Checked : Qt::Unchecked); break;
            default: return QVariant(); break;
        }
    }

    return QVariant();
}

QVariant pCatParametersModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QStringList headers;
    headers << tr( "Name" ) << tr("Default Value") << tr( "Mandatory" ) << tr( "Read only" );
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

    QList< QSharedPointer< pCatParameter > >::iterator pct = _pCatParams.begin() + index.row();
    if (role == Qt::UserRole+1) {
        QSharedPointer< pCatParameter > pgr = value.value< QSharedPointer< pCatParameter >>();
        pct->reset( pgr.get() );
        emit dataChanged( index.sibling(index.row(), 0), index.sibling(index.row(), 3), {Qt::DisplayRole, Qt::EditRole, Qt::UserRole, Qt::UserRole+1});
        return true;
    }
    else if( index.column()==1 && (role == Qt::DisplayRole || role== Qt::EditRole) ) {
        (*pct)->setDefaultValue( value );
        emit dataChanged( index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    else if( index.column() == 2 && role == Qt::CheckStateRole ) {
        (*pct)->setMandatory( (value==Qt::Checked) );
        emit dataChanged( index, index, {Qt::CheckStateRole} );
        return true;
    }
    else if( index.column() == 3 && role == Qt::CheckStateRole ) {
        (*pct)->setReadOnly( (value==Qt::Checked) );
        emit dataChanged( index, index, {Qt::CheckStateRole} );
        return true;
    }
    return false;
}

bool pCatParametersModel::insertRows(int position, int rows, const QModelIndex &parent) {
    if (parent.isValid() || position < 0 || position > _pCatParams.size())
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    QList< QSharedPointer< pCatParameter > >::iterator pos = _pCatParams.begin() + position + rows - 1;
    for (int i=0; i<rows; i++) {
        _pCatParams.insert( pos, QSharedPointer< pCatParameter >(nullptr)) ;
        pos++;
    }
    const bool success = (pos != _pCatParams.end() );
    //parentItem->insertChildren(position,                                              rows);
    endInsertRows();

    return success;
}

bool pCatParametersModel::removeRows(int position, int rows, const QModelIndex &parent) {
    if (parent.isValid() || position < 0 || position+rows-1 >= _pCatParams.size())
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    for (int i=0; i<rows; i++)
        _pCatParams.removeAt( position );
    const bool success = true;
    endRemoveRows();

    return success;
}
