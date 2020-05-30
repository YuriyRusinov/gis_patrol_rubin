/*
 * @brief Виджет графического соединения с БД "Защита-дозор"
 * logindbform.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QDialog>
#include <QMap>

namespace Ui {
    class login_db_form;
}

class LoginDbForm : public QDialog {
public:
    LoginDbForm( const QMap<int, QString>& accessLevels, QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    virtual ~LoginDbForm();

    QString getUser() const;
    void setUser( QString user );

    QString getPassword() const;
    void setPassword( QString pass );

    int getCurrentAccessLevel() const;
    void setCurrentAccessLevel( int acc );

    QString getDb() const;
    void setDb( QString dbName );

    QString getHost() const;
    void setHost( QString host );

    qint64 getPort() const;
    void setPort( qint64 port );

private:
    Ui::login_db_form* _UI;

private:
    Q_OBJECT
};
