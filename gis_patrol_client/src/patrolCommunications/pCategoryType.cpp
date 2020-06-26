/*
 * @brief Класс описывает тип категории средств коммуникации
 * pCategoryType.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pCategoryType.h"

pCategoryType::pCategoryType( qint64 id, QString name, QString desc, bool isRef )
    : _idCatType( id ), _name( name ), _description( desc ), _isReference( isRef ) {
}

pCategoryType::pCategoryType( const pCategoryType& pct )
    : _idCatType( pct._idCatType ), _name( pct._name ), _description( pct._description ),_isReference( pct._isReference) {
}

pCategoryType::~pCategoryType() {}

qint64 pCategoryType::getId() const {
    return _idCatType;
}

void pCategoryType::setId( qint64 id ) {
    _idCatType = id;
}

QString pCategoryType::getName() const {
    return _name;
}

void pCategoryType::setName( QString name ) {
    _name = name;
}

QString pCategoryType::getDesc() const {
    return _description;
}

void pCategoryType::setDesc( QString desc ) {
    _description = desc;
}

bool pCategoryType::isReference() const {
    return _isReference;
}

void pCategoryType::setReference( bool value ) {
    _isReference = value;
}
