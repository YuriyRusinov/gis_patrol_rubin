/*
 * @brief Класс содержащий фактическую величину параметра узла связи.
 * pParamValue.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QDateTime>
#include <QSharedPointer>
#include <QVariant>

class pCatParameter;
class pIObject;

class pParamValue {
public:
    pParamValue( );
    pParamValue( QSharedPointer< pCatParameter > pCatPar, QVariant value );
    pParamValue( const pParamValue& pVal );
    ~pParamValue( );

    qint64 getId() const;
    void setId( qint64 id );

    const QVariant& value() const;
    QVariant& value();
    void setValue( const QVariant& val );
    QString valueForInsert() const;

    QSharedPointer< pCatParameter > getCatParam() const;
    void setCatParam( QSharedPointer< pCatParameter > pCatParam );

    QSharedPointer< pIObject > ioSrc() const;
    void setIoSrc( QSharedPointer< pIObject > io );

    const QString& description() const;
    void setDescription( const QString& desc );

    const QDateTime& startDateTime() const;
    void setStartDateTime( const QDateTime& sdt );

    const QDateTime& finishDateTime() const;
    void setFinishDateTime( const QDateTime& fdt );

    const QDateTime& insertDateTime() const;
    void setInsertDateTime( const QDateTime& idt );

    bool isActual() const;
    void setActual( bool val );

private:
    qint64 _id; // в таблице tbl_parameter_values
    QSharedPointer< pCatParameter > _parameter;
    mutable QVariant _value;
    QSharedPointer< pIObject > _ioSrc;

    QString _description;
    QDateTime _startDateTime;
    QDateTime _finishDateTime;
    QDateTime _insertDateTime;
    bool _isActual;
};
