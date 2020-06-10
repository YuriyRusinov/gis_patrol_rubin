/*
 * @brief Класс описывает тип центра связи
 * pCommCenterType.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pCommCenterType.h"

pCommCenterType::pCommCenterType(int type, QString name, QString shortName)
    : _type(pCommCenterType::pCenterTypes(type)),
    _name(name),
    _shortName(shortName) {
}

pCommCenterType::pCommCenterType(const pCommCenterType& pct)
    : _type(pct._type),
    _name(pct._name),
    _shortName(pct._shortName) {
}

pCommCenterType::~pCommCenterType() {
}

pCommCenterType::pCenterTypes pCommCenterType::getType() const {
    return _type;
}

void pCommCenterType::setType(int type) {
    _type = pCommCenterType::pCenterTypes(type);
}

QString pCommCenterType::getName() const {
    return _name;
}

void pCommCenterType::setName( QString name ) {
    _name = name;
}

QString pCommCenterType::getShortName() const {
    return _shortName;
}

void pCommCenterType::setShortName( QString sName ) {
    _shortName = sName;
}
