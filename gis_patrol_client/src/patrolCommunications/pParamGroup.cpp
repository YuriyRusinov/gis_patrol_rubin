/*
 * @brief Класс, описывающий группу, содержащую параметр узла связи,
 * pParamGroup.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include "pParameter.h"
#include "pParamGroup.h"

pParamGroup::pParamGroup(qint64 id, QString name, QSharedPointer< pParamGroup > parent)
    : _id( id ),
    _name( name ),
    _parentGroup( parent ) {
}

pParamGroup::pParamGroup(const pParamGroup& PG)
    : _id( PG._id ),
    _name( PG._name ),
    _parentGroup( PG._parentGroup) {
}

pParamGroup::~pParamGroup() {
}

qint64 pParamGroup::getId() const {
    return _id;
}

void pParamGroup::setId( qint64 id ) {
    _id = id;
}

QSharedPointer< pParamGroup > pParamGroup::getParent() const {
    return _parentGroup;
}

void pParamGroup::setParent( QSharedPointer< pParamGroup > parent ) {
    _parentGroup = parent;
}

QString pParamGroup::getName() const {
    return _name;
}

void pParamGroup::setName( QString name ) {
    _name = name;
}

const QMap< qint64, QSharedPointer< pParamGroup > >& pParamGroup::getChildGroups() const {
    return _childGroups;
}

void pParamGroup::setChildGroups( const QMap< qint64, QSharedPointer< pParamGroup > >& childGroups ) {
    _childGroups = childGroups;
}

void pParamGroup::clearChildGroups() {
    _childGroups.clear();
}

void pParamGroup::addChildGroup( qint64 id, QSharedPointer< pParamGroup > pChildG ) {
    if (pChildG.isNull())
        return;
    _childGroups.insert( id, pChildG );
}

const QMap< qint64, QSharedPointer< pParameter > >& pParamGroup::getParameters() const {
    return _parameters;
}

void pParamGroup::setParameters( const QMap< qint64, QSharedPointer< pParameter > >& params ) {
    _parameters = params;
}

void pParamGroup::clearParameters() {
    _parameters.clear();
}

void pParamGroup::addParameter( pParameter* param ) {
    if (!param)
        return;
    _parameters.insert( param->getId(), QSharedPointer< pParameter >(param) );
}

QSharedPointer< const pParamGroup > pParamGroup::childGroupForId (qint64 id, bool recursive) const {
    if (this->_id == id)
        return QSharedPointer< const pParamGroup >(this);

    QMap<qint64, QSharedPointer< pParamGroup >>::const_iterator pg = _childGroups.constFind (id);
    if( pg != _childGroups.constEnd() )
        return pg.value();
    else if (recursive) {
        QSharedPointer< const pParamGroup > apg ( nullptr );
        for( pg = _childGroups.constBegin(); pg != _childGroups.constEnd() && apg == nullptr; pg++) {
            apg = pg.value()->childGroupForId( id, recursive );
        }
        return apg;
    }

    return nullptr;
}

QSharedPointer< pParamGroup > pParamGroup::childGroupForId (qint64 id, bool recursive) {
    if ( this->_id == id )
        return QSharedPointer< pParamGroup >(this);

    QMap<qint64, QSharedPointer< pParamGroup >>::const_iterator pg = _childGroups.constFind (id);
    if( pg != _childGroups.constEnd() )
        return pg.value();
    else if (recursive) {
        QSharedPointer< pParamGroup > apg ( nullptr );
        for( pg = _childGroups.constBegin(); pg != _childGroups.constEnd() && apg == nullptr; pg++) {
            apg = pg.value()->childGroupForId( id, recursive );
        }
        return apg;
    }

    return nullptr;
}

int pParamGroup::getEntity() const {
    return 0;
}
