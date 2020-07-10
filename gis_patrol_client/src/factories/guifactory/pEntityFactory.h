/*
 * @brief Базовый класс для классов-фабрик
 * pEntityFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QObject>

class pEntityFactory : public QObject {
public:
    //
    // В классах-фабриках, наследующих данному формирует виджет со списком сущностей,
    //  таких как параметр, категория, и т.д.
    //
    virtual QWidget* GUIView( QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() ) = 0;

protected:
    pEntityFactory( QObject* parent=nullptr );
    virtual ~pEntityFactory();
    pEntityFactory( const pEntityFactory& ef ) = delete;
    pEntityFactory& operator= ( const pEntityFactory& ef ) = delete;

signals:
    void viewWidget(QWidget* w);

private:
    friend class PatrolSingleton;

private:
    Q_OBJECT
};
