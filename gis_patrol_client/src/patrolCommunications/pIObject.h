/*
 * @brief Класс описывает информационный объект, являющийся справочником или документом
 * pIObject.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QDateTime>
#include <QColor>
#include <QIcon>
#include <QSharedPointer>
#include <QString>
#include <QUuid>

#include "pRecord.h"

class pCategory;
class pParamValue;

class pIObject : public pRecord {
public:
    pIObject( );
    pIObject( qint64 id,
              QSharedPointer< pCategory > pCat,
              QString name,
              QString description = QString());
    pIObject( const pIObject& io );
    virtual ~pIObject( );

    QSharedPointer< pCategory > getCategory( ) const;
    void setCategory( QSharedPointer< pCategory > pCat );

    QString getTableName( ) const;
    void setTableName( QString tableName );

    const QDateTime& insertTime( ) const;
    QDateTime& insertTime( );
    void setInsertTime( const QDateTime& dt );

    bool isSystem( ) const;
    void setSystem( bool sys );

    bool isGlobal( ) const;
    void setGlobal( bool global );

    qint64 getAuthor( ) const;
    void setAuthor( qint64 idAuthor );

    int getMacLabel( ) const;
    void setMacLabel( int ml );

    QString getInfo( ) const;
    void setInfo( const QString& info );

    QString getRefTableName( ) const;
    void setRefTableName( const QString& refTableName );

    QString getAuthorEmail( ) const;
    void setAuthorEmail( const QString& authorEmail );

    const QList< QSharedPointer< pParamValue > >& paramValues() const;
    QList< QSharedPointer< pParamValue > >& paramValues();
    void setParamValues( QList< QSharedPointer< pParamValue > >& pVals );
    void addParamValue( QSharedPointer< pParamValue > pVal );
    QSharedPointer< pParamValue > paramValue( qint64 id ) const;
    //
    // удаляет из списка значений все значения атрибута с указанным id
    //
    qint64 removeParamValue( qint64 _id );
    //
    // удаляет из списка значений указанное значение
    //
    qint64 removeParamValue( QSharedPointer< pParamValue > pVal );
    //
    // удаляет из списка значений значение с указанным порядковым индексом
    //
    qint64 removeParamValueInd( qint64 index );

private:
    qint64 _id;
    QSharedPointer< pCategory > _pCategory;
    QString _tableName;

    QDateTime _insertTime;
    /* Определяет происхождение ИО.
     * Если ИО является системным, то он существует в системе изначально 
     * при ее установке, если не является системным, то он создается 
     * пользователями во время их работы.
     * Как правило, системные ИО являются контейнерными, т.е. справочниками.
     * Системные ИО удалить нельзя. Можно только модифицировать 
     * (добавлять, удалять, изменять) их экземпляры ИО. */
    bool _isSystem;
    bool _isGlobal;
    qint64 _idUser;
    int _idMaclabel;

    QString _information;

    QString _refTableName;
    QString _authorEmail;

    QList< QSharedPointer< pParamValue > > _paramValues;

}; /* -----  end of class PIObject  ----- */
