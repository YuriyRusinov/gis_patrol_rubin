/*
 * @brief Синглтон работы с БД и графикой приложения "Защита-дозор"
 * patrolsingleton.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <gis_patroldatabase.h>
#include <gis_patrolpgdatabase.h>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pParamGuiFactory.h>
#include <pCatGuiFactory.h>
#include "patrolguiapp.h"
#include "patrolsingleton.h"

PatrolSingleton* PatrolSingleton::_instance = nullptr;

PatrolSingleton* PatrolSingleton::getPatrolS( QObject* parent ) {
    if (!_instance) {
        _instance = new PatrolSingleton( parent );
    }

    return _instance;
}

PatrolSingleton::PatrolSingleton( QObject* parent )
    : QObject( parent ),
    _dataBase( new GISPatrolPGDatabase ),
    _pga( new PatrolGuiApp (_dataBase) ),
    _pdbLoader( new pDBLoader( _dataBase ) ),
    _pdbWriter( new pDBWriter( _dataBase ) ),
    _pguif( new pParamGUIFactory( _pdbLoader, _pdbWriter ) ),
    _pcatf( new pCatGuiFactory( _pdbLoader, _pdbWriter, _pguif ) )
{
    if (_instance) {
        qFatal("There should be only one PatrolSingleton object");
    }
    _instance = this;
    qDebug() << __PRETTY_FUNCTION__;
}

PatrolSingleton::~PatrolSingleton() {
    qDebug() << __PRETTY_FUNCTION__;
    _instance = nullptr;
}

void PatrolSingleton::resetPatrol() {
    delete _instance;
}
