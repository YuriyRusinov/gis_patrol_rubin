/*
 * @brief Класс-фабрика, управляющий визуальным отображением записей
 * pGuiFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QObject>

class QWidget;

class PGUIFactory : public QObject {
public:
    //
    // Пока заглушка для отладки механизма
    //
    QWidget* GUIView(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

signals:
    void viewWidget(QWidget* w);

private:
    PGUIFactory( QObject* parent = nullptr );
    ~PGUIFactory ();

    friend class PatrolSingleton;

private:
    Q_OBJECT
};
