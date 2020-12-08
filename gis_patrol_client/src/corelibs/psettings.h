/*
 * @brief Класс работы с локальными настройками приложения "Защита-дозор"
 * psettings.h
 *
 * Класс предназначен для сохранения и получения настроек работы. В начале работы приложения необходимо получить указатель на
 *  экземпляр данного класса. За это отвечает класс PatrolGuiApp (методы PatrolGuiApp::getSettings()).

 * Важно отметить, что всегда доступен ТОЛЬКО ОДИН указатель на pSettings. Т.е. в настоящее время поддерживается
 *  только один набор настроек пользователя. Данный класс имеет только приватные конструкторы, т.е. создать экземпляр данного класса
 *  самостоятельно невозможно.

 * Работа с настройками производится с помощью интерфейса класса библиотеки Qt QSettings. В данном классе доступны методы
 * редактирования, чтения и восстановления параметров и поиска параметра по заданным имени группы и имени параметра.
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QSettings>

class pSettings : public QSettings {
public:
    QString getParam( const QString& keyname ) const;
    QString getGroupParam ( const QString& group, const QString& keyname );

public slots:
    void editSettings ( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    void writeSettings ( const QString& group, const QString& key, const QString & val );
    void readSettings ( );

private:
    friend class PatrolGuiApp;
    pSettings( QSettings::Scope scope, QObject* parent = nullptr );
    pSettings( QObject* parent = nullptr );
    pSettings( const QString& fileName, QSettings::Format format, QObject* parent = nullptr );
    pSettings( QSettings::Format format, QSettings::Scope scope, const QString &organization, const QString& application = QString(), QObject* parent = nullptr );
    pSettings( QSettings::Scope scope, const QString& organization, const QString& application = QString(), QObject* parent = nullptr );
    pSettings( const QString& organization, const QString& application = QString(), QObject* parent = nullptr );
    virtual ~pSettings();

private:
    Q_OBJECT
};
