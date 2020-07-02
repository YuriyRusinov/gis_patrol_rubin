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

    qint64 insertCategoryParam( qint64 idCategory, QSharedPointer< pCatParameter> pCParam ) const;

    GISPatrolDatabase* getDb() const;
    void setDb( GISPatrolDatabase* db );

private:
    friend class PatrolSingleton;

    GISPatrolDatabase* _db;

private:
    Q_OBJECT
};
