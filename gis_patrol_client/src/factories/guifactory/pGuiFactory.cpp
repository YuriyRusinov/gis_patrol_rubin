/*
 * @brief Класс-фабрика, управляющий визуальным отображением записей
 * pGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QWidget>
#include "pGuiFactory.h"

PGUIFactory::PGUIFactory( QObject* parent )
    : QObject( parent ) {
}

PGUIFactory::~PGUIFactory () {
}

QWidget* PGUIFactory::GUIView(QWidget* parent, Qt::WindowFlags flags) {
    QWidget* w = new QWidget( parent, flags );
    emit viewWidget( w );
    return w;
}
