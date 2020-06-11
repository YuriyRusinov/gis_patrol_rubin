/*
 * @brief Класс, описывающий параметры узла связи,
 * pCommNode.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pCommNode.h"

pCommNode::pCommNode(QString name, // Наименование
                     QString call_sign, // Позывной
                     qint64 identification_number, // Условный номер
                     const QDomDocument& scheme_order, // Схема-приказ
                     const QDomDocument& scheme_node, // Схема узла
                     const QDomDocument& equipment_layout // План размещения оборудования
        ) :
    _name( name ),
    _call_sign( call_sign ),
    _identification_number( identification_number ),
    _scheme_order( scheme_order ),
    _scheme_node( scheme_node ),
    _equipment_layout( equipment_layout ) {
}

pCommNode::pCommNode(const pCommNode& pcn) :
    _name( pcn._name ),
    _call_sign( pcn._call_sign ),
    _identification_number( pcn._identification_number ),
    _scheme_order( pcn._scheme_order ),
    _scheme_node( pcn._scheme_node ),
    _equipment_layout( pcn._equipment_layout) {
}

pCommNode::~pCommNode() {
}

QString pCommNode::getName() const {
    return _name;
}

void pCommNode::setName( QString name ) {
    _name = name;
}

QString pCommNode::getCallSign() const {
    return _call_sign;
}

void pCommNode::setCallSign( QString cs ) {
    _call_sign = cs;
}

qint64 pCommNode::getIdentNumber() const {
    return _identification_number;
}

void pCommNode::setIdentNumber( qint64 num ) {
    _identification_number = num;
}

const QDomDocument& pCommNode::getSchemeOrder() const {
    return _scheme_order;
}

void pCommNode::setSchemeOrder( const QDomDocument& scheme_order ) {
    _scheme_order = scheme_order;
}

const QDomDocument& pCommNode::getSchemeNode() const {
    return _scheme_node;
}

void pCommNode::setSchemeNode( const QDomDocument& scheme_node ) {
    _scheme_node = scheme_node;
}

const QDomDocument& pCommNode::getLayout() const {
    return _equipment_layout;
}

void pCommNode::setLayout (const QDomDocument& equipment_layout) {
    _equipment_layout = equipment_layout;
}
