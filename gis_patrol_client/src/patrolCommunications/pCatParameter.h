/*
 * @brief Класс, описывающий параметр узла связи в рамках категории,
 * pCatParameter.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QSharedPointer>
#include <QVariant>

#include "pParameter.h"

class pCatParameter : public pParameter {
public:
    pCatParameter( const pParameter& par = pParameter(), bool is_mandatory = false, bool is_readonly = false, QVariant defaultValue = QVariant(), int orderCat=-1 );
    pCatParameter( const pCatParameter& pcp );
    ~pCatParameter();

    bool isMandatory() const;
    void setMandatory( bool val );

    bool isReadOnly() const;
    void setReadOnly( bool val );

    QVariant getDefaultValue() const;
    void setDefaultValue( QVariant val );

    int getOrder() const;
    void setOrder( int val );

    inline bool operator< (const pCatParameter& pcp) const { return getOrder() < pcp.getOrder(); }

private:
    bool _is_mandatory;
    bool _is_readonly;
    QVariant _defaultValue;
    int _orderCat;
};

inline bool compareCatParams( QSharedPointer< const pCatParameter > item1, QSharedPointer< const pCatParameter > item2 ) {
    return item1->getOrder() < item2->getOrder();
}

Q_DECLARE_METATYPE( pCatParameter );
Q_DECLARE_METATYPE( QSharedPointer< pCatParameter > );