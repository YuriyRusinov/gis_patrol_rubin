/*
 * @brief Класс работы с БД и графикой приложения "Защита-дозор"
 * patrolguiapp.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QSettings>
#include <QtDebug>

#include <gis_patroldatabase.h>
#include "ui/logindbform.h"
#include "psettings.h"
#include "patrolguiapp.h"

const QString ORGANIZATION = "Rubin";
const QString PROJECT_NAME = "GIS Patrol";

PatrolGuiApp::PatrolGuiApp(GISPatrolDatabase* db, QObject* parent) : QObject (parent), _dataBase(db), _patrolSettings( nullptr ) {
}

PatrolGuiApp::~PatrolGuiApp() {
    delete _patrolSettings;
}

bool PatrolGuiApp::GUIConnect(const QMap<int, QString>& accLevels, QWidget* parent, Qt::WindowFlags flags) {
    LoginDbForm* logForm = new LoginDbForm(accLevels, parent, flags);
    _patrolSettings = getPatrolSettings ();
        //new QSettings(, "GIS Patrol");
    _patrolSettings->beginGroup("System settings");
    _patrolSettings->beginGroup("Database");
    QString userName = _patrolSettings->value("username").toString();
    logForm->setUser( userName );
    int accLevel = _patrolSettings->value("security level", 0).toInt();
    logForm->setCurrentAccessLevel( accLevel );
    QString dbName = _patrolSettings->value("db_name").toString();
    logForm->setDb( dbName );
    QString dbHost = _patrolSettings->value("db_host").toString();
    logForm->setHost( dbHost );
    qint64 dbPort = _patrolSettings->value("db_port", 5432).toInt();
    logForm->setPort( dbPort );
    bool isConn = false;
    while( !isConn && logForm->exec() != QDialog::Rejected) {
        qDebug() << __PRETTY_FUNCTION__;
        isConn = _dataBase->connect( logForm->getHost(),
                                     logForm->getDb(),
                                     logForm->getUser(),
                                     logForm->getPassword(),
                                     QString::number(logForm->getPort())
                                   );
        if( isConn ) {
            _patrolSettings->setValue( "username", logForm->getUser());
            _patrolSettings->setValue( "security level", QString::number( logForm->getCurrentAccessLevel()) );
            _patrolSettings->setValue( "db_name", logForm->getDb() );
            _patrolSettings->setValue( "db_host", logForm->getHost() );
            _patrolSettings->setValue( "db_port", QString::number(logForm->getPort()) );
        }
    }

    _patrolSettings->endGroup(); // database
    _patrolSettings->endGroup(); // system
    return isConn;
}

void PatrolGuiApp::disconnectFromDb() {
    _dataBase->disconnect(false);
    if(!_dataBase->connected())
        dbDisconnected();
}

void PatrolGuiApp::dbDisconnected() {
    emit disconnected();
}

/* @brief Метод возвращает локальные настройки приложения.
 *
 * ВАЖНО: в данном приложении может присутствовать только 1 экземпляр данного класса
 * Внимание: нельзя удалять или модифицировать данную область памяти
 */
pSettings* PatrolGuiApp::getPatrolSettings() {
    if( _patrolSettings == nullptr ) {
        _patrolSettings = new pSettings( ORGANIZATION, PROJECT_NAME );
    }
    _patrolSettings->readSettings();

    return _patrolSettings;
}
