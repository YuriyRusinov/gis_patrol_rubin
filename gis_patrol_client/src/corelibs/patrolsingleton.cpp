/*
 * @brief Синглтон работы с БД и графикой приложения "Защита-дозор"
 * patrolsingleton.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QCoreApplication>
#include <QDir>
#include <QLocale>
#include <QTranslator>
#include <QtDebug>
#include <gis_patroldatabase.h>
#include <gis_patrolpgdatabase.h>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pParamGuiFactory.h>
#include <pCatGuiFactory.h>
#include <pIOGuiFactory.h>
#include "psettings.h"
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
    _pParamF( new pParamGUIFactory( _pdbLoader, _pdbWriter ) ),
    _pcatf( new pCatGuiFactory( _pdbLoader, _pdbWriter, _pParamF ) ),
    _piof( new pIOGuiFactory( _pdbLoader, _pdbWriter, _pParamF, _pcatf ) ),
    _tor( new QTranslator( nullptr ) )
{
    if (_instance) {
        qFatal("There should be only one PatrolSingleton object");
    }
    _instance = this;
    qDebug() << __PRETTY_FUNCTION__;
}

PatrolSingleton::~PatrolSingleton() {
    qDebug() << __PRETTY_FUNCTION__;
    delete _tor;
    _instance = nullptr;
}

void PatrolSingleton::resetPatrol() {
    delete _instance;
}

void PatrolSingleton::installTranslator() const {
    pSettings* pSet = _pga->getPatrolSettings();
    if( !pSet )
        return;

    pSet->beginGroup("System settings");
    QString translPath = pSet->value("Translator path", QDir::currentPath()+QDir::separator()+QString("transl")).toString();
    pSet->endGroup();
    QString translFileName = /*translPath+QDir::separator()+*/QString("patrol_ru");
    //QLocale ruLocale( QLocale::Russian );
    bool isLoaded = _tor->load( translFileName, translPath );//, QDir::separator() );
    qDebug() << __PRETTY_FUNCTION__ << translPath << translFileName << isLoaded;
    if( isLoaded ) {
        pSet->beginGroup("System settings");
        pSet->setValue("Translator path", translPath);
        pSet->endGroup();
    }

    bool isInstalled = QCoreApplication::installTranslator( _tor );
    qDebug() << __PRETTY_FUNCTION__ << isInstalled;
}
