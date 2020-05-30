/*
 * @brief Главный виджет приложения "Защита-дозор"
 * patrolmainwindow.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QMainWindow>

class QMdiArea;
class QToolBar;

namespace Ui {
    class patrol_main_window;
}

class PatrolSingleton;

class PatrolMainWindow : public QMainWindow {
public:
    PatrolMainWindow(QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());
    virtual ~PatrolMainWindow();

private slots:
    void slotDbConnect();
    void slotDbDisconnect();

private:
    //
    // Functions
    //
    void initActions();
private:
    //
    // Variables
    //
    Ui::patrol_main_window* _UI;
    QToolBar* _tbAct;
    QMdiArea* _mdiArea;
    PatrolSingleton* _patrolS;

private:
    Q_OBJECT
};
