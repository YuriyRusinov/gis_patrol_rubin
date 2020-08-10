/* 
 * @brief Класс описывает визуальную модель отображения данных с возможностью их выбора
 * pCheckableDataModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <pCategory.h>
#include <pCatParameter.h>
#include <pParamValue.h>
#include <pRecordC.h>
#include "pCheckableDataModel.h"

pCheckableDataModel::pCheckableDataModel ( QSharedPointer< pParamValue > pRefParamValue, QSharedPointer< pCategory > pCategory, const QMap< qint64, QSharedPointer< pRecordCopy > >& records, QObject* parent ) :
    pRecordDataModel( pCategory, records, parent ),
    _pReferenceParameterValue( pRefParamValue ) {
}
    
pCheckableDataModel::~pCheckableDataModel() {
    _pReferenceParameterValue.reset();
}

QVariant pCheckableDataModel::data (const QModelIndex& index, int role) const {
    if( role == Qt::CheckStateRole && index.column() == 0 ) {
        //
        // TODO: необходимо прописать сохранение данных из промежуточных таблиц
        //
        QList< qint64 > p_values;
        QVariant val = _pReferenceParameterValue->value();
        QList< QVariant > vals = val.toList();
        for( int i=0; i<vals.size(); i++ )
            p_values.append( vals[i].toLongLong() );
        qint64 id = pRecordDataModel::data(index, Qt::UserRole).toLongLong();
        if( p_values.contains( id ) )
            return QVariant( Qt::Checked );
        else
            return QVariant( Qt::Unchecked );
    }

    return pRecordDataModel::data(index, role);
}

bool pCheckableDataModel::setData (const QModelIndex& index, const QVariant& value, int role) {
    if( role == Qt::CheckStateRole && index.column() == 0 ) {
        //
        // TODO: необходимо прописать сохранение данных из промежуточных таблиц
        //
        QList< qint64 > p_values;
        QVariant val = _pReferenceParameterValue->value();
        QList< QVariant > vals = val.toList();
        for( int i=0; i<vals.size(); i++ )
            p_values.append( vals[i].toLongLong() );
        qint64 id = pRecordDataModel::data(index, Qt::UserRole).toLongLong();
        //qDebug() << __PRETTY_FUNCTION__ << role << index << value << id << (value.toInt() == Qt::Checked);
        if( value.toInt() == Qt::Checked ) {
            p_values.append( id );
        }
        else {
            int id_f = p_values.indexOf( id );
            p_values.erase( p_values.begin() + id_f );
        }
        vals.clear();
        for ( int i = 0; i < p_values.size(); i++ ) {
            vals.append( QVariant( p_values[i] ) );
        }
        QVariant listVal(vals);
        //qDebug() << __PRETTY_FUNCTION__ << p_values << listVal;
        _pReferenceParameterValue->setValue( listVal );
        emit dataChanged( index, index );
        return true;
    }
    bool isSet = pRecordDataModel::setData( index, value, role );
    return isSet;
}
