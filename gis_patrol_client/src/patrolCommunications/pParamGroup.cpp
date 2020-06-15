/*
 * @brief Класс, описывающий группу, содержащую параметр узла связи,
 * pParamGroup.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pParamGroup.h"

pParamGroup::pParamGroup(qint64 id, QString name, pParamGroup* parent)
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

shared_ptr< pParamGroup > pParamGroup::getParent() const {
    return _parentGroup;
}

void pParamGroup::setParent( shared_ptr< pParamGroup > parent ) {
    _parentGroup = parent;
}

QString pParamGroup::getName() const {
    return _name;
}

void pParamGroup::setName( QString name ) {
    _name = name;
}
