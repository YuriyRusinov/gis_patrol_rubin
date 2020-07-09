/*
 * @brief Класс содержащий фактическую величину параметра узла связи.
 * pParamValue.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pCatParameter.h"
#include "pIObject.h"
#include "pParamValue.h"

pParamValue::pParamValue( )
    : _id( -1 ),
    _parameter( nullptr ),
    _value( QVariant() ),
    _columnValue( QString() ),
    _ioSrc( nullptr ),
    _description( QString() ),
    _startDateTime( QDateTime() ),
    _finishDateTime( QDateTime() ),
    _insertDateTime( QDateTime() ),
    _isActual( false ) {
}

pParamValue::pParamValue( QSharedPointer< pCatParameter > pCat, QVariant value )
    : _id( -1 ),
    _parameter( pCat ),
    _value( value ),
    _columnValue( QString() ),
    _ioSrc( nullptr ),
    _description( QString() ),
    _startDateTime( QDateTime() ),
    _finishDateTime( QDateTime() ),
    _insertDateTime( QDateTime() ),
    _isActual( false ) {
}

pParamValue::pParamValue( const pParamValue& pVal )
    : _id( pVal._id ),
    _parameter( pVal._parameter ),
    _value( pVal._value ),
    _columnValue( pVal._columnValue ),
    _ioSrc( pVal._ioSrc ),
    _description( pVal._description ),
    _startDateTime( pVal._startDateTime ),
    _finishDateTime( pVal._finishDateTime ),
    _insertDateTime( pVal._insertDateTime ),
    _isActual( pVal._isActual ) {
}

pParamValue::~pParamValue( ) {
}

qint64 pParamValue::getId() const {
    return _id;
}

void pParamValue::setId( qint64 id ) {
    _id = id;
}

const QVariant& pParamValue::value() const {
    return _value;
}

QVariant& pParamValue::value() {
    return _value;
}

void pParamValue::setValue( const QVariant& val ) {
    _value = val;
}

QString pParamValue::valueForInsert() const {
    //
    // TODO: написать реальное строковое представление для различных типов параметров
    //       пока для отработки элементов не актуально
    //
    return _value.toString();
}

const QString& pParamValue::getColumnValue() const {
    return _columnValue;
}

void pParamValue::setColumnValue( const QString& cVal ) {
    _columnValue = cVal;
}

QSharedPointer< pCatParameter > pParamValue::getCatParam() const {
    return _parameter;
}

void pParamValue::setCatParam( QSharedPointer< pCatParameter > pCatParam ) {
    _parameter = pCatParam;
}

QSharedPointer< pIObject > pParamValue::ioSrc() const {
    return _ioSrc;
}

void pParamValue::setIoSrc( QSharedPointer< pIObject > io ) {
    _ioSrc = io;
}

const QString& pParamValue::description() const {
    return _description;
}

void pParamValue::setDescription( const QString& desc ) {
    _description = desc;
}

const QDateTime& pParamValue::startDateTime() const {
    return _startDateTime;
}

void pParamValue::setStartDateTime( const QDateTime& sdt ) {
    _startDateTime = sdt;
}

const QDateTime& pParamValue::finishDateTime() const {
    return _finishDateTime;
}

void pParamValue::setFinishDateTime( const QDateTime& fdt ) {
    _finishDateTime = fdt;
}

const QDateTime& pParamValue::insertDateTime() const {
    return _insertDateTime;
}

void pParamValue::setInsertDateTime( const QDateTime& idt ) {
    _insertDateTime = idt;
}

bool pParamValue::isActual() const {
    return _isActual;
}

void pParamValue::setActual( bool val ) {
    _isActual = val;
}
