/*
 * @brief Синглтон работы с БД и графикой приложения "Защита-дозор"
 * patrolsingleton.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QObject>

class GISPatrolDatabase;
class PatrolGuiApp;
class pParamGUIFactory;
class pCatGuiFactory;
class pDBLoader;
class pDBWriter;

class PatrolSingleton : public QObject {
public:
    static PatrolSingleton* getPatrolS( QObject* parent=nullptr );
    static void resetPatrol();

    GISPatrolDatabase* getDb() const { return _dataBase; }
    PatrolGuiApp* getGUIObj() const { return _pga; }
    pParamGUIFactory* getGUIFactory() const { return _pguif; }
    pCatGuiFactory* getCatGUIFactory() const { return _pcatf; }
    pDBLoader* getDbLoader() const { return _pdbLoader; }
    pDBWriter* getDbWriter() const { return _pdbWriter; }

private:
    PatrolSingleton(QObject* parent=nullptr);
    PatrolSingleton(const PatrolSingleton& ps) = delete;
    PatrolSingleton& operator=(const PatrolSingleton& ps) = delete;
    ~PatrolSingleton();

    static PatrolSingleton* _instance;

    mutable GISPatrolDatabase* _dataBase;
    mutable PatrolGuiApp* _pga;
    mutable pDBLoader* _pdbLoader;
    mutable pDBWriter* _pdbWriter;
    mutable pParamGUIFactory* _pguif;
    mutable pCatGuiFactory* _pcatf;

private:
    Q_OBJECT
};
