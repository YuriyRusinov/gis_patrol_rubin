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

class QTranslator;

class GISPatrolDatabase;
class PatrolGuiApp;
class pParamGUIFactory;
class pCatGuiFactory;
class pDBLoader;
class pDBWriter;
class pIOGuiFactory;

class PatrolSingleton : public QObject {
public:
    static PatrolSingleton* getPatrolS( QObject* parent=nullptr );
    static void resetPatrol();

    GISPatrolDatabase* getDb() const { return _dataBase; }
    PatrolGuiApp* getGUIObj() const { return _pga; }
    pParamGUIFactory* getParamGUIFactory() const { return _pParamF; }
    pCatGuiFactory* getCatGUIFactory() const { return _pcatf; }
    pIOGuiFactory* getIOGUIFactory() const { return _piof; }
    pDBLoader* getDbLoader() const { return _pdbLoader; }
    pDBWriter* getDbWriter() const { return _pdbWriter; }
    void installTranslator() const;

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
    mutable pParamGUIFactory* _pParamF;
    mutable pCatGuiFactory* _pcatf;
    mutable pIOGuiFactory* _piof;
    QTranslator* _tor;

private:
    Q_OBJECT
};
