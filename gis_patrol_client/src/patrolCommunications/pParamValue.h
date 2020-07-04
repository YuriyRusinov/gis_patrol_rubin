/*
 * @brief Класс содержащий фактическую величину параметра узла связи.
 * pParamValue.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QSharedPointer>
#include <QVariant>

class pCatParameter;
class pIObject;

class pParamValue {
public:
    pParamValue( );
    pParamValue( QSharedPointer< pCatParameter > pCat, QVariant value );
    pParamValue( const pParamValue& pVal );
    ~pParamValue( );
};
