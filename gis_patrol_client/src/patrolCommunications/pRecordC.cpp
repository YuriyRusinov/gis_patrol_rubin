/*
 * @brief Класс описывает запись в БД, относящуюся к информационному объекту-справочнику
 * pRecordC.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <defines.h>
#include "pCatParameter.h"
#include "pIObject.h"
#include "pParamValue.h"
#include "pRecordC.h"
#include <QtDebug>

pRecordCopy::pRecordCopy() : pRecord(),
    _io( nullptr ),
    _paramValues( QList< QSharedPointer< pParamValue > >() ) {
}

pRecordCopy::pRecordCopy( const pRecordCopy& PRC ) : pRecord( PRC ),
    _io( PRC._io ),
    _paramValues( PRC._paramValues ) {
}

pRecordCopy::pRecordCopy( qint64 id, const QString& name, QSharedPointer< pIObject > io )
    : pRecord( id, name ),
    _io( io ),
    _paramValues( QList< QSharedPointer< pParamValue > >() ) {
}

pRecordCopy::~pRecordCopy() {
}

const QList< QSharedPointer< pParamValue > >& pRecordCopy::paramValues() const {
    return _paramValues;
}

QList< QSharedPointer< pParamValue > >& pRecordCopy::paramValues() {
    return _paramValues;
}

void pRecordCopy::setParamValues( const QList< QSharedPointer< pParamValue > >& pVals ) {
    _paramValues = pVals;
}

QSharedPointer< const pParamValue > pRecordCopy::paramValueIndex( int index ) const {
    QSharedPointer< const pParamValue > pV( nullptr );
    if( index < 0 || index >= _paramValues.size() )
        return pV;

    pV = _paramValues.at( index );
    return pV;
}

QSharedPointer< pParamValue > pRecordCopy::paramValueIndex( int index ) {
    QSharedPointer< pParamValue > pV( nullptr );
    if( index < 0 || index >= _paramValues.size() )
        return pV;

    pV = _paramValues[index];
    return pV;
}

QSharedPointer< const pParamValue > pRecordCopy::paramValue( qint64 id ) const {
    QSharedPointer< const pParamValue > pV( nullptr );
    int n = _paramValues.size();

    for ( int i = 0; i < n && pV.isNull(); i++ ) {
        if( _paramValues[i]->getCatParam()->getId() == id )
            pV = _paramValues[i];
    }
    return pV;
}

QSharedPointer< pParamValue > pRecordCopy::paramValue( qint64 id ) {
    QSharedPointer< pParamValue > pV( nullptr );
    int n = _paramValues.size();

    for ( int i = 0; i < n && pV.isNull(); i++ ) {
        if( _paramValues[i]->getCatParam()->getId() == id )
            pV = _paramValues[i];
    }
    return pV;
}

QSharedPointer< const pParamValue > pRecordCopy::paramValue( QString code ) const {
    QSharedPointer< const pParamValue > pV( nullptr );
    int n = _paramValues.size();

    for ( int i = 0; i < n && pV.isNull(); i++ ) {
        if( QString::compare( _paramValues[i]->getCatParam()->getCode(), code, Qt::CaseInsensitive ) == 0 )
            pV = _paramValues[i];
    }
    return pV;
}

QSharedPointer< pParamValue > pRecordCopy::paramValue( QString code ) {
    QSharedPointer< pParamValue > pV( nullptr );
    int n = _paramValues.size();

    for ( int i = 0; i < n && pV.isNull(); i++ ) {
        if( QString::compare( _paramValues[i]->getCatParam()->getCode(), code, Qt::CaseInsensitive ) == 0 )
            pV = _paramValues[i];
    }
    return pV;
}

QSharedPointer< pIObject > pRecordCopy::getIO() const {
    return _io;
}

void pRecordCopy::setIO( QSharedPointer< pIObject > io ) {
    _io = io;
}

void pRecordCopy::setName( const QString& name ) {
    pRecord::setName( name );
    QSharedPointer< pParamValue > pV = paramValue( ATTR_NAME );
    if( pV.isNull() )
        qWarning( QObject::tr("Parameter 'name' does not present in object copy attributes!").toUtf8().constData() );
    else
        pV->setValue( QVariant( name ) );
}

void pRecordCopy::setId(qint64 newId) {
    pRecord::setId( newId );
    QSharedPointer< pParamValue > pV = paramValue( ATTR_ID );
    if( pV.isNull() )
        qWarning( QObject::tr("Parameter 'id' does not present in object copy attributes!").toUtf8().constData() );
    else
        pV->setValue( QVariant( newId ) );
}

void pRecordCopy::setCode( const QString& code ) {
    pRecord::setCode( code );
    QSharedPointer< pParamValue > pV = paramValue( ATTR_CODE );
    if( pV.isNull() )
        qWarning( QObject::tr("Parameter 'code' does not present in object copy attributes!").toUtf8().constData() );
    else
        pV->setValue( QVariant( code ) );
}

void pRecordCopy::setDesc( const QString& desc ) {
    pRecord::setDesc( desc );
    QSharedPointer< pParamValue > pV = paramValue( ATTR_DESCRIPTION );
    if( pV.isNull() )
        qWarning( QObject::tr("Parameter 'description' does not present in object copy attributes!").toUtf8().constData() );
    else
        pV->setValue( QVariant( desc ) );
}
