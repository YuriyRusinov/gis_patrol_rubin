/*
 * @brief Загрузчик данных из БД приложения "Защита-дозор"
 * patroldbloader.h
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
class GISPatrolResult;
class pParamGroup;
class pParameter;
class pParamType;
class pCategory;
class pCategoryType;
class pCatParameter;
class pIObject;
class pRecordCopy;
class pParamValue;

class pDBLoader : public QObject {
public:
    pDBLoader(GISPatrolDatabase* db=nullptr, QObject* parent=nullptr );
    ~pDBLoader();

    GISPatrolDatabase* getDb() const;
    void setDb( GISPatrolDatabase* db );

    QMap< qint64, QSharedPointer< pParamGroup > > loadGroupedParameters() const;
    QMap< qint64, QSharedPointer< pParameter > > loadParameters( QSharedPointer< pParamGroup > pGroup ) const;
    QMap< qint64, QSharedPointer< pParamType > > loadAvailParamTypes() const;

    QSharedPointer< pParamGroup > loadParamGroup( qint64 idGroup ) const;

    QMap< qint64, QSharedPointer< pCategory > > loadCategories() const;

    QMap< qint64, QSharedPointer< pCategoryType > > loadAvailCatTypes() const;

    QSharedPointer< pCategory > loadCategory( qint64 idCat ) const;

    QSharedPointer< pParameter> loadParameter( qint64 idParam ) const;

    QSharedPointer< pIObject > loadIO( qint64 id ) const;
    QSharedPointer< pIObject > loadIOByTableName( QString tableName ) const;

    QSharedPointer< pRecordCopy > loadCopy( qint64 id, QSharedPointer< pIObject > io ) const;
    QMap< qint64, QSharedPointer< pRecordCopy > > loadRecords( QSharedPointer< pIObject > io ) const;
    QMap< qint64, QSharedPointer< pRecordCopy > > loadRecords( QSharedPointer< pCategory > pCat, QString tableName ) const;

private:
    //
    // Functions
    //
    QSharedPointer< pCategory > loadChildCat( qint64 idCat ) const;
    QMap< qint64, QSharedPointer< pCatParameter > > loadCatParameters( qint64 idCat ) const;

    QString generateSelectRecQuery( QSharedPointer< const pCategory > pCat0, const QString& tableName, bool isSys, qint64 id=-1 ) const;

    qint64 loadIOId(const QString& tableName) const;

    QList< QSharedPointer< pParamValue > > loadParamValues( QSharedPointer< pCategory > pTableCat, GISPatrolResult * gpr, int i ) const;

private:
    friend class PatrolSingleton;

    GISPatrolDatabase* _db;

private:
    Q_OBJECT
};
