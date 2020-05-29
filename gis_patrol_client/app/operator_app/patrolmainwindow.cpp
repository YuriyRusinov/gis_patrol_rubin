/*
 * @brief Главный виджет приложения "Защита-дозор"
 * patrolmainwindow.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAction>
#include <QMdiArea>
#include <QToolBar>
#include <QtDebug>

#include <patrolsingleton.h>
#include "patrolmainwindow.h"
#include "ui_patrol_main_window.h"

PatrolMainWindow::PatrolMainWindow(QWidget* parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    _UI(new Ui::patrol_main_window),
    _tbAct(new QToolBar),
    _mdiArea(new QMdiArea) {
    _UI->setupUi( this );
    this->addToolBar(Qt::TopToolBarArea, _tbAct);
    this->setCentralWidget(_mdiArea);
    _patrolS = PatrolSingleton::getPatrolS();
    qDebug() << __PRETTY_FUNCTION__ << (_patrolS != nullptr);

    this->initActions();

    QObject::connect(_UI->actConnect, &QAction::triggered, this, &PatrolMainWindow::slotDbConnect);
    QObject::connect(_UI->actDisconnect, &QAction::triggered, this, &PatrolMainWindow::slotDbDisconnect);
    QObject::connect(_UI->actQuit, &QAction::triggered, this, &QMainWindow::close);
}

PatrolMainWindow::~PatrolMainWindow() {
    _patrolS->resetPatrol();
    delete _mdiArea;
    delete _tbAct;
    delete _UI;
}

void PatrolMainWindow::slotDbConnect() {
    qDebug() << __PRETTY_FUNCTION__;
}

void PatrolMainWindow::slotDbDisconnect() {
    qDebug() << __PRETTY_FUNCTION__;
}

void PatrolMainWindow::initActions() {
    QAction* aDbConnect = _tbAct->addAction(QIcon(":/patrol/db_connect.png"), tr("Connect..."));
    aDbConnect->setToolTip(tr("Connect to database"));
    QObject::connect(aDbConnect, &QAction::triggered, this, &PatrolMainWindow::slotDbConnect);

    QAction* aDbDisconnect = _tbAct->addAction(QIcon(":/patrol/db_disconnect.png"), tr("Disconnect..."));
    aDbDisconnect->setToolTip(tr("Disconnect from database"));
    QObject::connect(aDbDisconnect, &QAction::triggered, this, &PatrolMainWindow::slotDbDisconnect);

    QAction* aQuit = _tbAct->addAction(QIcon(":/patrol/exit.png"), tr("Quit"));
    QObject::connect(aQuit, &QAction::triggered, this, &QMainWindow::close);
}
