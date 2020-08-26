/*
 * @brief Записывальщик данных в БД приложения "Защита-дозор"
 * patroldbwriter.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QMap>
#include <QObject>
#include <QSharedPointer>

class GISPatrolDatabase;
class pParamGroup;
class pParameter;
class pCategory;
class pCatParameter;
class pRecordCopy;
class pIObject;
class pParamValue;

class pDBWriter : public QObject {
public:
    pDBWriter(GISPatrolDatabase* db=nullptr, QObject* parent=nullptr );
    ~pDBWriter();

    qint64 writeParamGroup( QSharedPointer< pParamGroup > pgr ) const;
    qint64 updateParamGroup( QSharedPointer< pParamGroup > pgr ) const;
    qint64 deleteParamGroup( qint64 idGroup ) const;
    qint64 insertParam( QSharedPointer< pParameter > pPar ) const;
    qint64 updateParam( QSharedPointer< pParameter > pPar ) const;
    qint64 deleteParam( qint64 idParam ) const;

    qint64 writeCategory( QSharedPointer< pCategory > pCat ) const;
    qint64 updateCategory( QSharedPointer< pCategory > pCat ) const;
    qint64 deleteCategory( qint64 idCat ) const;

    qint64 insertRecord( QSharedPointer< pRecordCopy > pRecord, QSharedPointer< pIObject > pIO ) const;
    qint64 updateRecord( QSharedPointer< pRecordCopy > pRecord, QSharedPointer< pIObject > pIO ) const;
    qint64 deleteRecord( QSharedPointer< pRecordCopy > pRecord, QSharedPointer< pIObject > pIO ) const;
    qint64 updateIORec( QSharedPointer< pRecordCopy > pRecord, QSharedPointer< pIObject > pIO, QSharedPointer< pIObject > pRecIO ) const;

private:
    qint64 insertCategoryParam( qint64 idCategory, QSharedPointer< pCatParameter> pCParam ) const;
    QList< qint64 > getCategoryParams( qint64 idCat ) const;
    qint64 deleteCategoryParam( qint64 idCat, qint64 idPar ) const;
    qint64 updateCategoryParam( qint64 idCategory, QSharedPointer< pCatParameter> pCParam ) const;
    QString generateUpdateRecQuery( QSharedPointer< pRecordCopy > pRecord, QString tableName, QString& exQuery ) const;
    QString generateInsertRecQuery( QSharedPointer< pRecordCopy > pRecord, QString tableName, QString& exQuery ) const;
    qint64 getNextSeq( QString tableName, QString columnName=QString("id") ) const;
    QString generateExternalQuery( QString tableName, QSharedPointer< const pParamValue > pValue, qint64 idRecord ) const;
    qint64 insertRecordParams( QSharedPointer< pIObject > pIO ) const;

public:
    GISPatrolDatabase* getDb() const;
    void setDb( GISPatrolDatabase* db );

private:
    friend class PatrolSingleton;

    GISPatrolDatabase* _db;

private:
    Q_OBJECT
};
