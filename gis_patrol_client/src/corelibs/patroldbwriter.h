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

class pDBWriter : public QObject {
public:
    pDBWriter(GISPatrolDatabase* db=nullptr, QObject* parent=nullptr );
    ~pDBWriter();

    GISPatrolDatabase* getDb() const;
    void setDb( GISPatrolDatabase* db );

private:
    friend class PatrolSingleton;

    GISPatrolDatabase* _db;

private:
    Q_OBJECT
};
