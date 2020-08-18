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
    void slotDbDisconnected();

    void slotCreateCategory();
    void slotAddParametersIntoCategory();
    void slotViewCategories();

    void slotViewReferences();

    void slotViewParameters();

    void slotAddWidget(QWidget* w);

    void slotCreateDocument();

private:
    //
    // Functions
    //
    void initActions();
    void setEnabled(bool enable);

private:
    //
    // Variables
    //
    Ui::patrol_main_window* _UI;
    QToolBar* _tbAct;
    QToolBar* _tbActReferences;
    QMdiArea* _mdiArea;
    PatrolSingleton* _patrolS;

private:
    Q_OBJECT
};
