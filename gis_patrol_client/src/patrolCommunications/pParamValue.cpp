/*
 * @brief Класс содержащий фактическую величину параметра узла связи.
 * pParamValue.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QByteArray>
#include <QBuffer>
#include <QString>
#include <QtDebug>

#include "pParamType.h"
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
    pParamType::PatrolParamTypes pType = _parameter->getParamType()->getId();
    if( _value.isNull() || ( _value.toString().isEmpty() && pType != pParamType::atCheckListEx ) )
        return ("null");
    QString resVal;
    switch( pType ) {
        case pParamType::atUndef: break;
        case pParamType::atBool: resVal = (_value.toBool() ? QString("true::boolean") : QString("false::boolean")); break;
        case pParamType::atList:
        case pParamType::atParent:
        case pParamType::atInt:
        case pParamType::atRecordColorRef:
        case pParamType::atRecordTextColorRef:
        case pParamType::atInt64:
                                 resVal = QString("%1").arg( _value.toLongLong()); break;
        case pParamType::atRecordColor:
        case pParamType::atRecordTextColor:
                                 resVal = QString("%1").arg( _value.toLongLong() ); break;
        case pParamType::atDouble:
                                 resVal = QString("%1").arg( _value.toDouble() ); break;
        case pParamType::atString:
        case pParamType::atText:
        case pParamType::atFixString:
        case pParamType::atUUID:
        case pParamType::atXML:
        case pParamType::atSVG:
                                 resVal = QString("'%1'").arg( _value.toString() ); break;
        case pParamType::atDate: resVal = _value.toDate().isValid() ?QString("'%1'::timestamp").arg( _value.toDate().toString(Qt::ISODate) ) : QString("null"); break;
        case pParamType::atDateTime:
        case pParamType::atDateTimeWithOffset:
        case pParamType::atDateTimeEx:
                                 resVal = _value.toDateTime().isValid() ? QString("'%1'::timestamptz").arg( _value.toDateTime().toString(Qt::ISODate) ) : QString("null"); break;
        case pParamType::atTime: _value.toTime().isValid() ? resVal = QString("'%1'::timestamptz").arg( _value.toTime().toString(Qt::ISODate) ) : QString("null"); break;
        case pParamType::atInterval: resVal = QString("interval '%1' day").arg( _value.toDouble() ); break;
        case pParamType::atIntervalH: resVal = QString("interval '%1' hour").arg( _value.toDouble() ); break;
        case pParamType::atBinary:
        case pParamType::atVideo: {
                                      QByteArray sVal (_value.toByteArray());
                                      int nc = sVal.length();
                                      for (int i=0; i<nc; i++) {
                                          char s = sVal.at(i);
                                          if (QChar (s) >= 0 && QChar (s)<=31)
                                              resVal += QString("\\\\%1").arg (s);
                                          else
                                              resVal += QString(s);
                                          }
                                          resVal.prepend("'");
                                          resVal.append("'");
                                          break;
                                    }
        case pParamType::atGeometry:
        case pParamType::atGeography:
        case pParamType::atGISMap: {
            resVal = QString("GeomFromEWKT('%1')::geometry").arg( _value.toString() );
            break;
        }
        case pParamType::atImage: {
            QByteArray ba;
            QBuffer buffer(&ba);
            buffer.open(QIODevice::WriteOnly);
            QImage im = _value.value< QImage >();
            im.save( &buffer, "XPM" );
            resVal = QString("'%1'").arg( QString(ba) );
            break;
        }
        case pParamType::atCheckListEx: case pParamType::atComplex: case pParamType::atHistogram: {
            qDebug() << __PRETTY_FUNCTION__ << _value;
            resVal = QString("'{%1}'").arg( _value.toStringList().join(",") );
            break;
        }
        case pParamType::atSysChildCategoryRef: case pParamType::atUserDef: break;
        case pParamType::atJSON: {
            resVal = QString("to_json('%1'::text)").arg( _value.toString() );
            break;
        }
        case pParamType::atJSONb: {
            resVal = QString("to_jsonb('%1'::text)").arg( _value.toString() );
            break;
        }
    }
    return resVal;
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
