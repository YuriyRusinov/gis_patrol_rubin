/*
 * @brief Загрузчик данных из БД приложения "Защита-дозор"
 * patroldbloader.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QObject>

#include <pParamGroup.h>
#include <pParameter.h>

class GISPatrolDatabase;

class pDBLoader : public QObject {
public:
    pDBLoader( QObject* parent=nullptr );
    ~pDBLoader();

    GISPatrolDatabase* getDb() const;
    void setDb( GISPatrolDatabase* db );

private:
    friend class PatrolSingleton;

    GISPatrolDatabase* _db;

private:
    Q_OBJECT
};
