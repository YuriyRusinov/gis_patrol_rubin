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
class pParamGroup;
class pParameter;
class pParamType;
class pCategory;
class pCategoryType;
class pCatParameter;

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

private:
    QSharedPointer< pCategory > loadChildCat( qint64 idCat ) const;
    QMap< qint64, QSharedPointer< pCatParameter > > loadCatParameters( qint64 idCat ) const;

private:
    friend class PatrolSingleton;

    GISPatrolDatabase* _db;

private:
    Q_OBJECT
};
