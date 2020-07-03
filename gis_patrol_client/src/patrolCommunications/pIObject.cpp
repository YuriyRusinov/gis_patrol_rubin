/*
 * @brief Класс описывает информационный объект, являющийся справочником или документом
 * pIObject.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pIObject.h"

pIObject::pIObject( ) {}
pIObject::pIObject( qint64 id,
              QSharedPointer< pCategory > pCat,
              QString name,
              QString description ) {
    Q_UNUSED( id );
    Q_UNUSED( pCat );
    Q_UNUSED( name );
    Q_UNUSED( description );
}

pIObject::pIObject( const pIObject& io ) {
    Q_UNUSED( io );
}
pIObject::~pIObject( ) {}

