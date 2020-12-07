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

PatrolGuiApp::PatrolGuiApp(GISPatrolDatabase* db, QObject* parent) : QObject (parent), _dataBase(db), _patrolSettings( new pSettings ) {
}

PatrolGuiApp::~PatrolGuiApp() {
    delete _patrolSettings;
}

bool PatrolGuiApp::GUIConnect(const QMap<int, QString>& accLevels, QWidget* parent, Qt::WindowFlags flags) {
    LoginDbForm* logForm = new LoginDbForm(accLevels, parent, flags);
    QSettings* patrolSettings = new QSettings("Rubin", "GIS Patrol");
    patrolSettings->beginGroup("System settings");
    patrolSettings->beginGroup("Database");
    QString userName = patrolSettings->value("username").toString();
    logForm->setUser( userName );
    int accLevel = patrolSettings->value("security level", 0).toInt();
    logForm->setCurrentAccessLevel( accLevel );
    QString dbName = patrolSettings->value("db_name").toString();
    logForm->setDb( dbName );
    QString dbHost = patrolSettings->value("db_host").toString();
    logForm->setHost( dbHost );
    qint64 dbPort = patrolSettings->value("db_port", 5432).toInt();
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
            patrolSettings->setValue( "username", logForm->getUser());
            patrolSettings->setValue( "security level", QString::number( logForm->getCurrentAccessLevel()) );
            patrolSettings->setValue( "db_name", logForm->getDb() );
            patrolSettings->setValue( "db_host", logForm->getHost() );
            patrolSettings->setValue( "db_port", QString::number(logForm->getPort()) );
        }
    }

    patrolSettings->endGroup(); // database
    patrolSettings->endGroup(); // system
    delete patrolSettings;
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
