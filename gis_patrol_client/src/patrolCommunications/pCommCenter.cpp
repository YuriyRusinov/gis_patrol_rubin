/*
 * @brief Класс, описывающий параметры центра управления связью,
 * pCommCenter.cpp
 *
 * * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include "pCommCenterType.h"
#include "pCommCenter.h"

pCommCenter::pCommCenter(QString name, pCommCenterType* pType)
    : _name(name),
    _pType (pType) {
}
    
pCommCenter::pCommCenter(const pCommCenter& PC)
    : _name(PC._name),
    _pType(PC._pType) {
}

pCommCenter::~pCommCenter() {
}

QString pCommCenter::getName() const {
    return _name;
}

void pCommCenter::setName(QString name) {
    _name = name;
}
