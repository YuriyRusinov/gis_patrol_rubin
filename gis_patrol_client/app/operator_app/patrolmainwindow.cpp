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
#include <patrolguiapp.h>
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
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    QObject::connect(pGuiApp, &PatrolGuiApp::disconnected, this, &PatrolMainWindow::slotDbDisconnected);
}

PatrolMainWindow::~PatrolMainWindow() {
    _patrolS->resetPatrol();
    delete _mdiArea;
    delete _tbAct;
    delete _UI;
}

void PatrolMainWindow::slotDbConnect() {
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    QMap<int, QString> accLevels;
    QStringList secLevels;
    secLevels << tr("Not secret") << tr("Confidential") << tr("Secret") << tr("Top secret");
    for(int i=0; i<secLevels.size(); i++)
        accLevels.insert(i, secLevels[i]);
    bool isConn = pGuiApp->GUIConnect(accLevels);
    _UI->actDisconnect->setEnabled( isConn );
    _UI->actConnect->setEnabled( !isConn );
}

void PatrolMainWindow::slotDbDisconnect() {
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    pGuiApp->disconnectFromDb();
    qDebug() << __PRETTY_FUNCTION__;
}

void PatrolMainWindow::initActions() {
    _UI->actConnect->setIcon(QIcon(":/patrol/db_connect.png"));
    _tbAct->addAction(_UI->actConnect);//QIcon(":/patrol/db_connect.png"), tr("Connect..."));
    _UI->actConnect->setToolTip(tr("Connect to database"));
    QObject::connect(_UI->actConnect, &QAction::triggered, this, &PatrolMainWindow::slotDbConnect);

    _UI->actDisconnect->setIcon(QIcon(":/patrol/db_disconnect.png"));
    _UI->actDisconnect->setEnabled( false );
    _tbAct->addAction(_UI->actDisconnect);
    _UI->actDisconnect->setToolTip(tr("Disconnect from database"));
    QObject::connect(_UI->actDisconnect, &QAction::triggered, this, &PatrolMainWindow::slotDbDisconnect);

    _UI->actQuit->setIcon(QIcon(":/patrol/exit.png"));
    _tbAct->addAction(_UI->actQuit);
    QObject::connect(_UI->actQuit, &QAction::triggered, this, &QMainWindow::close);
}

void PatrolMainWindow::slotDbDisconnected() {
    _UI->actConnect->setEnabled( true );
    _UI->actDisconnect->setEnabled( false );
}
