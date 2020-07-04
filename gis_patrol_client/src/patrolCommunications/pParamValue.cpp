/*
 * @brief Класс содержащий фактическую величину параметра узла связи.
 * pParamValue.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pParamValue.h"

pParamValue::pParamValue( ) {}
pParamValue::pParamValue( QSharedPointer< pCatParameter > pCat, QVariant value ) {
    Q_UNUSED( pCat );
    Q_UNUSED( value );
}

pParamValue::pParamValue( const pParamValue& pVal ) {
    Q_UNUSED( pVal );
}

pParamValue::~pParamValue( ) {
}
