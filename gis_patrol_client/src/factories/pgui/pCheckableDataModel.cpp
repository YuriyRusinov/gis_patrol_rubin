/* 
 * @brief Класс описывает визуальную модель отображения данных с возможностью их выбора
 * pCheckableDataModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
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
        return QVariant();
    }

    return pRecordDataModel::data(index, role);
}

bool pCheckableDataModel::setData (const QModelIndex& index, const QVariant& value, int role) {
    if( role == Qt::CheckStateRole && index.column() == 0 ) {
        //
        // TODO: необходимо прописать сохранение данных из промежуточных таблиц
        //
        return false;
    }
    bool isSet = pRecordDataModel::setData( index, value, role );
    return isSet;
}
