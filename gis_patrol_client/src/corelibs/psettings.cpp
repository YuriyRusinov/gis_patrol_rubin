/*
 * @brief Класс работы с локальными настройками приложения "Защита-дозор"
 * psettings.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QMessageBox>
#include <QtDebug>
#include "psettings.h"
#include "ui/psettingsform.h"

#if QT_VERSION >= 0x051300
pSettings::pSettings( QSettings::Scope scope, QObject* parent )
    : QSettings( scope, parent ) {
}
#endif

pSettings::pSettings( QObject* parent )
    : QSettings( parent ) {
}

pSettings::pSettings( const QString& fileName, QSettings::Format format, QObject* parent )
    : QSettings( fileName, format, parent ) {
}

pSettings::pSettings( QSettings::Format format, QSettings::Scope scope, const QString& organization, const QString& application, QObject* parent )
    : QSettings( format, scope, organization, application, parent ) {
}

pSettings::pSettings( QSettings::Scope scope, const QString& organization, const QString& application, QObject* parent )
    : QSettings( scope, organization, application, parent ) {
}

pSettings::pSettings( const QString& organization, const QString& application, QObject* parent )
    : QSettings( organization, application, parent ) {
}

pSettings::~pSettings() {
}

/* @brief Метод осуществляет поиск параметра в текущей группе по его имени, 
 если параметр не найден, то возвращается пустая строка.
*/ 
QString pSettings::getParam( const QString& keyname ) const {
    QString wstr = this->value (keyname).toString ();
    //qDebug () << "key = " << keyname << " value = " << wstr;
    return wstr;
}

/* @brief Метод осуществляет поиск параметра в заданной группе по его имени, 
 если параметр не найден, то возвращается пустая строка.
*/
QString pSettings::getGroupParam ( const QString& group, const QString& keyname ) {
    this->beginGroup (group);
    QString val = this->getParam (keyname);
    this->endGroup ();
    return val;
}

void pSettings::editSettings ( QWidget* parent, Qt::WindowFlags flags ) {
    pSettingsForm * setForm = new pSettingsForm (this, parent, flags);
    if ( setForm->exec() == QDialog::Accepted )
    {
        
        QMessageBox::information ( 0, tr("Save settings"),
                tr("You have to restart your application in order to changes take effect"),
                QMessageBox::Ok );
    }

    delete setForm;
}

void pSettings::writeSettings ( const QString& group, const QString& key, const QString & val ) {
    this->beginGroup (group);
    this->setValue (key, val);
    this->endGroup ();
}

void pSettings::readSettings ( ) {
    QStringList groups = this->childGroups();
    for (int i=0; i<groups.count(); i++)
    {
        this->beginGroup ( groups[i] );
        if (this->childGroups ().count () > 0)
        {
            qDebug () << __PRETTY_FUNCTION__ << QString ("Sub group");
            readSettings ();
        }
        this->endGroup ();
        QStringList keys = this->childKeys ();
        for (int ii=0; ii<keys.count(); ii++)
            this->setValue ( keys[ii], this->value (keys[ii]));
    }
}
