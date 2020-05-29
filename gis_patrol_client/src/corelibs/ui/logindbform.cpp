/*
 * @brief Виджет графического соединения с БД "Защита-дозор"
 * logindbform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QIntValidator>

#include "logindbform.h"
#include "ui_login_db_form.h"

LoginDbForm::LoginDbForm( const QMap<int, QString>& accessLevels, QWidget* parent, Qt::WindowFlags flags ) :
    QDialog( parent, flags ),
    _UI( new Ui::login_db_form ) {
    _UI->setupUi( this );
    for (QMap<int, QString>::const_iterator pacc = accessLevels.constBegin();
            pacc != accessLevels.constEnd();
            pacc++) {
        _UI->cbLevel->addItem( pacc.value(), pacc.key() );
    }
    QValidator * portVal = new QIntValidator( 1, 5500, this);
    _UI->lEPort->setValidator( portVal );

    QObject::connect(_UI->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(_UI->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

LoginDbForm::~LoginDbForm() {
    delete _UI;
}

QString LoginDbForm::getUser() const {
    return _UI->leUserName->text();
}

void LoginDbForm::setUser( QString user ) {
    _UI->leUserName->setText( user );
}

QString LoginDbForm::getPassword() const {
    return _UI->lePassword->text();
}

void LoginDbForm::setPassword( QString pass ) {
    _UI->lePassword->setText( pass );
}

int LoginDbForm::getCurrentAccessLevel() const {
    return _UI->cbLevel->currentData().toInt();
}

void LoginDbForm::setCurrentAccessLevel( int acc ) {
    int index = _UI->cbLevel->findData( acc );
    _UI->cbLevel->setCurrentIndex( index );
}

QString LoginDbForm::getDb() const {
    return _UI->lEDatabase->text();
}

void LoginDbForm::setDb( QString dbName ) {
    _UI->lEDatabase->setText( dbName );
}

QString LoginDbForm::getHost() const {
    return _UI->lEHost->text();
}

void LoginDbForm::setHost( QString host ) {
    _UI->lEHost->setText( host );
}

qint64 LoginDbForm::getPort() const {
    bool ok;
    return _UI->lEPort->text().toLongLong(&ok, 10);
}

void LoginDbForm::setPort( qint64 port ) {
    _UI->lEPort->setText( QString::number( port ) );
}
