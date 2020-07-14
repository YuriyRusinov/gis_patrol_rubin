/*
 * @brief Класс описывает запись в БД, относящуюся к информационному объекту-справочнику
 * pRecordC.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QMetaType>
#include <QSharedPointer>

#include "pRecord.h"

class pIObject;
class pParamValue;

class pRecordCopy : public pRecord {
public:
    pRecordCopy();
    pRecordCopy( const pRecordCopy& PRC );
    pRecordCopy( qint64 id, const QString& name, QSharedPointer< pIObject > io );
    ~pRecordCopy();

    const QList< QSharedPointer< pParamValue > >& paramValues() const;
    QList< QSharedPointer< pParamValue > >& paramValues();
    void setParamValues( const QList< QSharedPointer< pParamValue > >& pVals );

    QSharedPointer< const pParamValue > paramValueIndex( int index ) const;
    QSharedPointer< pParamValue > paramValueIndex( int index );
    QSharedPointer< const pParamValue > paramValue( qint64 id ) const;
    QSharedPointer< pParamValue > paramValue( qint64 id );
    QSharedPointer< const pParamValue > paramValue( QString code ) const;
    QSharedPointer< pParamValue > paramValue( QString code );

    QSharedPointer< pIObject > getIO() const;
    void setIO( QSharedPointer< pIObject > io );

    void setName( const QString& name ) override;
    void setId(qint64 newId) override;
    void setCode( const QString& code ) override;
    void setDesc( const QString& desc ) override;

private:
    QSharedPointer< pIObject > _io;
    QList< QSharedPointer< pParamValue > > _paramValues;
};

Q_DECLARE_METATYPE( QSharedPointer< const pRecordCopy > );
Q_DECLARE_METATYPE( QSharedPointer< pRecordCopy > );
