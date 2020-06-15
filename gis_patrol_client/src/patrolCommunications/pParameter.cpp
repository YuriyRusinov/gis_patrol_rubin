/*
 * @brief Класс, описывающий параметр узла связи,
 * pParameter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pParamType.h"
#include "pParamGroup.h"
#include "pParameter.h"

pParameter::pParameter(qint64 id, pParamType* pType, pParamGroup* pGroup, QString pCode, QString pName, QString pTitle, QString tableName, QString columnName, bool isSystem)
    : _id( id ),
    _pType( pType ),
    _pGroup( pGroup ),
    _code( pCode ),
    _name( pName ),
    _title( pTitle ),
    _tableName( tableName ),
    _columnName( columnName ),
    _isSystem( isSystem ) {
}

pParameter::pParameter(const pParameter& P1)
    : _id( P1._id ),
    _pType( P1._pType ),
    _pGroup( P1._pGroup ),
    _code( P1._code ),
    _name( P1._name ),
    _title( P1._title ),
    _tableName( P1._tableName ),
    _columnName( P1._columnName ),
    _isSystem( P1._isSystem ) {
}

pParameter::~pParameter() {
}

qint64 pParameter::getId() const {
    return _id;
}

void pParameter::setId( qint64 id ) {
    _id = id;
}

shared_ptr< pParamType > pParameter::getParamType() const {
    return _pType;
}

void pParameter::setParamType( shared_ptr< pParamType > pType ) {
    _pType = pType;
}

shared_ptr< pParamGroup > pParameter::getParamGroup() const {
    return _pGroup;
}

void pParameter::setParamGroup( shared_ptr< pParamGroup > pGroup ) {
    _pGroup = pGroup;
}

QString pParameter::getCode() const {
    return _code;
}

void pParameter::setCode( QString code ) {
    _code = code;
}

QString pParameter::getName() const {
    return _name;
}

void pParameter::setName( QString name ) {
    _name = name;
}

QString pParameter::getTitle() const {
    return _title;
}

void pParameter::setTitle( QString title ) {
    _title = title;
}

QString pParameter::getTableName() const {
    return _tableName;
}

void pParameter::setTableName( QString tableName ) {
    _tableName = tableName;
}

QString pParameter::getColumnName() const {
    return _columnName;
}

void pParameter::setColumnName( QString columnName ) {
    _columnName = columnName;
}

bool pParameter::getSystem() const {
    return _isSystem;
}

void pParameter::setSystem( bool isSys ) {
    _isSystem = isSys;
}
