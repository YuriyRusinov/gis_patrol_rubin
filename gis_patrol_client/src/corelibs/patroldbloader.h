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

class pDBLoader : public QObject {
public:
    pDBLoader( QObject* parent=nullptr );
    ~pDBLoader();

    GISPatrolDatabase* getDb() const;
    void setDb( GISPatrolDatabase* db );

    QMap< qint64, QSharedPointer< pParamGroup > > loadGroupedParameters() const;
    QMap< qint64, QSharedPointer< pParameter > > loadParameters( pParamGroup* pGroup ) const;

private:
    pParamGroup* loadParamGroup( int idGroup ) const;

private:
    friend class PatrolSingleton;

    GISPatrolDatabase* _db;

private:
    Q_OBJECT
};
