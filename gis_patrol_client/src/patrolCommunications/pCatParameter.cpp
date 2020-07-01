/*
 * @brief Класс, описывающий параметр узла связи в рамках категории,
 * pCatParameter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pCatParameter.h"

pCatParameter::pCatParameter( const pParameter& par, bool is_mandatory, bool is_readonly, QVariant defaultValue, int orderCat )
    : pParameter( par ),
    _is_mandatory( is_mandatory ),
    _is_readonly( is_readonly ),
    _defaultValue( defaultValue ),
    _orderCat( orderCat ) {
}

pCatParameter::pCatParameter( const pCatParameter& pcp )
    : pParameter( pcp ),
    _is_mandatory( pcp._is_mandatory ),
    _is_readonly( pcp._is_readonly ),
    _defaultValue( pcp._defaultValue ),
    _orderCat( pcp._orderCat ) {
}

pCatParameter::~pCatParameter() {
}

bool pCatParameter::isMandatory() const {
    return _is_mandatory;
}

void pCatParameter::setMandatory( bool val ) {
    _is_mandatory = val;
}

bool pCatParameter::isReadOnly() const {
    return _is_readonly;
}

void pCatParameter::setReadOnly( bool val ) {
    _is_readonly = val;
}

QVariant pCatParameter::getDefaultValue() const {
    return _defaultValue;
}

void pCatParameter::setDefaultValue( QVariant val ) {
    _defaultValue = val;
}

int pCatParameter::getOrder() const {
    return _orderCat;
}

void pCatParameter::setOrder( int val ) {
    _orderCat = val;
}

const int& pCatParameter::paramOrder() const {
    return _orderCat;
}

int& pCatParameter::paramOrder() {
    return _orderCat;
}

void findCatParamsByOrder( QVector< qint64 >& res, const QMap< qint64, QSharedPointer< pCatParameter > >& params, int orderVal ) {
    QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pp;
    for( pp=params.constBegin(); pp != params.constEnd(); pp++) {
        if (pp.value()->paramOrder() > orderVal)
            res.append( pp.key() );
    }
}
