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
#include <QMdiSubWindow>
#include <QToolBar>
#include <QtDebug>

#include <defines.h>
#include <patrolsingleton.h>
#include <patrolguiapp.h>
#include <pParamGuiFactory.h>
#include <pCatGuiFactory.h>
#include <pIObject.h>
#include <pCatParameter.h>
#include <pParamValue.h>
#include <pCategory.h>
#include <pRecordC.h>
#include <pIOGuiFactory.h>
#include <pCIOEditor.h>
#include <patroldbloader.h>
#include "patrolmainwindow.h"
#include "ui_patrol_main_window.h"

PatrolMainWindow::PatrolMainWindow(QWidget* parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    _UI(new Ui::patrol_main_window),
    _tbAct(new QToolBar),
    _tbActReferences(new QToolBar),
    _mdiArea(new QMdiArea) {
    _UI->setupUi( this );
    this->addToolBar(Qt::TopToolBarArea, _tbAct);
    this->addToolBar(Qt::TopToolBarArea, _tbActReferences);
    this->setCentralWidget(_mdiArea);
    _patrolS = PatrolSingleton::getPatrolS();
    qDebug() << __PRETTY_FUNCTION__ << (_patrolS != nullptr);

    this->initActions();
    setEnabled( false );
    PatrolGuiApp* pGuiApp = _patrolS->getGUIObj();
    pParamGUIFactory* pGuiFactory = _patrolS->getParamGUIFactory();
    pCatGuiFactory* pCatGuiF = _patrolS->getCatGUIFactory();
    pIOGuiFactory* pIOGuiF = _patrolS->getIOGUIFactory();
    QObject::connect( pGuiApp, &PatrolGuiApp::disconnected, this, &PatrolMainWindow::slotDbDisconnected );
    QObject::connect( pGuiFactory, &pParamGUIFactory::viewWidget, this, &PatrolMainWindow::slotAddWidget );
    QObject::connect( pCatGuiF, &pCatGuiFactory::viewWidget, this, &PatrolMainWindow::slotAddWidget );
    QObject::connect( pIOGuiF, &pIOGuiFactory::viewWidget, this, &PatrolMainWindow::slotAddWidget );
}

PatrolMainWindow::~PatrolMainWindow() {
    _patrolS->resetPatrol();
    delete _mdiArea;
    delete _tbActReferences;
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
    setEnabled( isConn );
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
    _tbAct->addAction(_UI->actDisconnect);
    _UI->actDisconnect->setToolTip(tr("Disconnect from database"));
    QObject::connect(_UI->actDisconnect, &QAction::triggered, this, &PatrolMainWindow::slotDbDisconnect);
    _tbAct->addSeparator();

    _UI->actQuit->setIcon(QIcon(":/patrol/exit.png"));
    _tbAct->addAction(_UI->actQuit);
    QObject::connect(_UI->actQuit, &QAction::triggered, this, &QMainWindow::close);

    _UI->actViewRef->setIcon(QIcon(":/patrol/view.png"));
    _tbActReferences->addAction(_UI->actViewRef);
    _UI->actViewRef->setToolTip(tr("View connection references"));
    QObject::connect(_UI->actViewRef, &QAction::triggered, this, &PatrolMainWindow::slotViewReferences);

    QObject::connect(_UI->actCreateCat, &QAction::triggered, this, &PatrolMainWindow::slotCreateCategory);

    _UI->actAddParametersIntoCat->setIcon(QIcon(":/patrol/add_parameter_to_cat.svg"));
    QObject::connect(_UI->actAddParametersIntoCat, &QAction::triggered, this, &PatrolMainWindow::slotAddParametersIntoCategory);

    _UI->actViewCat->setIcon(QIcon(":/patrol/view_parameters.svg"));
    _tbActReferences->addAction( _UI->actViewCat );
    QObject::connect( _UI->actViewCat, &QAction::triggered, this, &PatrolMainWindow::slotViewCategories );

    _UI->actViewParameters->setIcon(QIcon(":/patrol/view_parameters.svg"));
    _tbActReferences->addAction(_UI->actViewParameters);
    QObject::connect(_UI->actViewParameters, &QAction::triggered, this, &PatrolMainWindow::slotViewParameters);

    QObject::connect( _UI->actCreateRef, &QAction::triggered, this, &PatrolMainWindow::slotCreateDocument );
}

void PatrolMainWindow::slotDbDisconnected() {
    setEnabled( false );
}

void PatrolMainWindow::slotViewReferences() {
    qDebug() << __PRETTY_FUNCTION__;
    pDBLoader* dbl = _patrolS->getDbLoader();
    QSharedPointer< pIObject > io = dbl->loadIO( IO_IO_ID );
    if( io.isNull() )
        return;
    QMap< qint64, QSharedPointer< pRecordCopy > > recs = dbl->loadRecords( io->getCategory(), io->getTableName() );
    qDebug() << __PRETTY_FUNCTION__ << io->getId() << recs.keys();
    pIOGuiFactory* pIOGuiF = _patrolS->getIOGUIFactory();
    pIOGuiF->GUIView();
}

void PatrolMainWindow::setEnabled(bool enable) {
    _UI->actViewRef->setEnabled( enable );
    _UI->actDisconnect->setEnabled( enable );
    _UI->actConnect->setEnabled( !enable );
    _UI->actCreateCat->setEnabled( enable );
    _UI->actAddParametersIntoCat->setEnabled( enable );
    _UI->actViewCat->setEnabled( enable );
    _UI->actViewParameters->setEnabled( enable );
    _UI->actCreateRef->setEnabled( enable );
}

void PatrolMainWindow::slotAddWidget(QWidget* w) {
    if (!w)
        return;

    w->setAttribute(Qt::WA_DeleteOnClose);
    QMdiSubWindow * subW = _mdiArea->addSubWindow(w);
    subW->setAttribute(Qt::WA_DeleteOnClose, true);

    w->show();
}

void PatrolMainWindow::slotViewParameters() {
    qDebug() << __PRETTY_FUNCTION__;
    pParamGUIFactory* pParamGuiFactory = _patrolS->getParamGUIFactory();
    pParamGuiFactory->GUIView( );
}

void PatrolMainWindow::slotCreateCategory() {
    qDebug() << __PRETTY_FUNCTION__;
    pCatGuiFactory* pCatGuiF = _patrolS->getCatGUIFactory();
    pCatGuiF->addPCategory( );
}

void PatrolMainWindow::slotAddParametersIntoCategory() {
    qDebug() << __PRETTY_FUNCTION__;
}

void PatrolMainWindow::slotViewCategories() {
    qDebug() << __PRETTY_FUNCTION__;
    pCatGuiFactory* pCatGuiF = _patrolS->getCatGUIFactory();
    pCatGuiF->GUIView();
}

void PatrolMainWindow::slotCreateDocument() {
    qDebug() << __PRETTY_FUNCTION__;
    pIOGuiFactory* pIOGuiF = _patrolS->getIOGUIFactory();
    pIOGuiF->createRecordCatEditor();
}
