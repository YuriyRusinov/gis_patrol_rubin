/*
 * @brief Класс описывает запись в БД 
 * pRecord.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pRecord.h"

pRecord::pRecord()
    : _id ( -1 ),
    _uuid( QString() ),
    _icon( QIcon() ),
    _recordFillColor( QColor() ),
    _recordTextColor( QColor() ),
    _name( QString() ),
    _code( QString() ),
    _description( QString() ),
    _parent( nullptr ) {
}

pRecord::pRecord( qint64 id, const QString& name, const QString& desc, const QString& code )
    : _id( id ),
    _uuid( QString() ),
    _icon( QIcon() ),
    _recordFillColor( QColor() ),
    _recordTextColor( QColor() ),
    _name( name ),
    _code( code ),
    _description( desc ),
    _parent( nullptr ) {
}

pRecord::pRecord( const pRecord& r )
    : _id( r._id ),
    _uuid( r._uuid ),
    _icon( r._icon ),
    _recordFillColor( r._recordFillColor ),
    _recordTextColor( r._recordTextColor ),
    _name( r._name ),
    _code( r._code ),
    _description( r._description ),
    _parent( r._parent ) {
}

pRecord::~pRecord() {
}

qint64 pRecord::getId() const {
    return _id;
}

void pRecord::setId( qint64 id ) {
    _id = id;
}

const QString& pRecord::getUUID() const {
    return _uuid;
}

void pRecord::setUUID( const QString& u ) {
    _uuid = u;
}

const QIcon& pRecord::getIcon() const {
    return _icon;
}

void pRecord::setIcon( const QIcon& i ) {
    _icon = i;
}

const QColor& pRecord::getFillColor() const {
    return _recordFillColor;
}

void pRecord::setFillColor( const QColor& fc ) {
    _recordFillColor = fc;
}

const QColor& pRecord::getTextColor() const {
    return _recordTextColor;
}

void pRecord::setTextColor( const QColor& tc ) {
    _recordTextColor = tc;
}

const QString& pRecord::getName() const {
    return _name;
}

void pRecord::setName( const QString& name ) {
    _name = name;
}

const QString& pRecord::getCode() const {
    return _code;
}

void pRecord::setCode( const QString& code ) {
    _code = code;
}

const QString& pRecord::getDesc() const {
    return _description;
}

void pRecord::setDesc( const QString& desc ) {
    _description = desc;
}

void pRecord::setParent( QSharedPointer< pRecord > p ) {
    _parent = p;
}

QSharedPointer< pRecord > pRecord::getParent() const {
    return _parent;
}
