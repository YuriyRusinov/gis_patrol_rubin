/*
 * @brief Класс, описывающий категорию средств коммуникации
 * pCategory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QtDebug>
#include "pCatParameter.h"
#include "pCategoryType.h"
#include "pCategory.h"

pCategory::pCategory(qint64 id, QString name, QString code, QSharedPointer< pCategoryType > pCatType) :
    _idCat( id ),
    _nameCat( name ),
    _codeCat( code ),
    _typeCat( pCatType ),
    _childCat( nullptr ),
    _categoryParams( QMap< qint64, QSharedPointer< pCatParameter > >() ),
    _isMainCat( pCatType.isNull() || pCatType->getId() != 10 ),
    _isSystemCat( false ) {
}

pCategory::pCategory(const pCategory& PCat)
    : _idCat ( PCat._idCat),
    _nameCat( PCat._nameCat ),
    _codeCat( PCat._codeCat ),
    _typeCat( PCat._typeCat ),
    _childCat( PCat._childCat ),
    _categoryParams( PCat._categoryParams ),
    _isMainCat( PCat._isMainCat ),
    _isSystemCat( PCat._isSystemCat ) {
}

pCategory::~pCategory() {
    _typeCat.reset();
    _childCat.reset();
    _categoryParams.clear();
}

qint64 pCategory::getId() const {
    return _idCat;
}

void pCategory::setId( qint64 id ) {
    _idCat = id;
}

QString pCategory::getName() const {
    return _nameCat;
}

void pCategory::setName( QString name ) {
    _nameCat = name;
}

QString pCategory::getCode() const {
    return _codeCat;
}

void pCategory::setCode( QString code ) {
    _codeCat = code;
}

QString pCategory::getDesc() const {
    return _descCat;
}

void pCategory::setDesc( QString desc ) {
    _descCat = desc;
}

QSharedPointer< pCategoryType > pCategory::getType() const {
    return _typeCat;
}

void pCategory::setType( QSharedPointer< pCategoryType > pct ) {
    _typeCat = pct;
}

QSharedPointer< pCategory > pCategory::getTableCat() const {
    return _childCat;
}

void pCategory::setTableCat( QSharedPointer< pCategory > tCat ) {
    _childCat = tCat;
}

QMap< qint64, QSharedPointer< pCatParameter > >& pCategory::categoryPars() {
    return _categoryParams;
}

const QMap< qint64, QSharedPointer< pCatParameter > >& pCategory::categoryPars() const {
    return _categoryParams;
}

void pCategory::setCategoryPars( const QMap< qint64, QSharedPointer< pCatParameter > >& cpars ) {
    _categoryParams = cpars;
}

void pCategory::clearPars() {
    _categoryParams.clear();
}

void pCategory::addParam( qint64 idParam, QSharedPointer< pCatParameter > p ) {
    _categoryParams.insert( idParam, p );
}

void pCategory::removeParam( qint64 idParam ) {
    QSharedPointer< pCatParameter > pPar = _categoryParams.value( idParam, nullptr );
    if (pPar)
        pPar.reset();
    int res = _categoryParams.remove( idParam );
    qDebug() << __PRETTY_FUNCTION__ << idParam << res;
}

bool pCategory::isMain() const {
    return _isMainCat;
}

void pCategory::setMain( bool val ) {
    _isMainCat = val;
}

bool pCategory::isSystem() const {
    return _isSystemCat;
}

void pCategory::setSystem( bool val ) {
    _isSystemCat = val;
}
