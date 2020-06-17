/*
 * @brief Класс, описывающий тип параметра узла связи,
 * pParamType.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pParamType.h"
#include "pParamView.h"

pParamType::pParamType( qint64 id, QString name, QString code, pParamView* pView )
    : _id( pParamType::PatrolParamTypes(id) ),
    _name( name ),
    _code( code ),
    _pView( pView ) {
}

pParamType::pParamType( const pParamType& PT )
    : _id( PT._id ),
    _name( PT._name ),
    _code( PT._code ),
    _pView( PT._pView ) {
}

pParamType::~pParamType() {
}

pParamType::PatrolParamTypes pParamType::getId() const {
    return _id;
}

void pParamType::setId( qint64 id ) {
    _id = pParamType::PatrolParamTypes( id );
}

shared_ptr< pParamView > pParamType::getView() const {
    return _pView;
}

void pParamType::setView( shared_ptr< pParamView > pView ) {
    _pView = pView;
}

QString pParamType::getName() const {
    return _name;
}

void pParamType::setName( QString name ) {
    _name = name;
}

QString pParamType::getCode() const {
    return _code;
}

void pParamType::setCode( QString code ) {
    _code = code;
}
