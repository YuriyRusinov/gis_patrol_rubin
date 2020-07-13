/*
 * @brief Виджет редактирования записей
 * pCIOEditor.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAction>
#include <QKeySequence>
#include <QGridLayout>
#include <QTabWidget>
#include <QToolBar>
#include <QtDebug>

#include <pCategory.h>
#include <pRecord.h>
#include <pRecordC.h>
#include <pIObject.h>
#include "pCIOEditor.h"

pCIOEditor::pCIOEditor( QSharedPointer< pCategory > pCategory,
                        QSharedPointer< pRecordCopy > pRec,
                        QSharedPointer< pIObject > pIO,
                        bool isIO,
                        QWidget* parent,
                        Qt::WindowFlags flags
                    )
    : QWidget( parent, flags ),
    _pCategory( pCategory ),
    _pRecord( pRec ),
    _pIO( pIO ),
    _isIO( isIO ),
    _tbIOActions( new QToolBar ),
    _tabW( new QTabWidget ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _tbIOActions, 0, 0, 1, 1 );
    grLay->addWidget( _tabW, 1, 0, 1, 1 );

    initActions();
}

pCIOEditor::~pCIOEditor() {
    delete _tbIOActions;
    delete _tabW;
}

QSharedPointer< const pCategory > pCIOEditor::getCategory() const {
    return _pCategory;
}

void pCIOEditor::setCategory( QSharedPointer< pCategory > pc ) {
    _pCategory = pc;
}

QSharedPointer< const pRecordCopy > pCIOEditor::getRecord() const {
    return _pRecord;
}

void pCIOEditor::setRecord ( QSharedPointer< pRecordCopy > pr ) {
    _pRecord = pr;
}

QSharedPointer< const pIObject > pCIOEditor::getObject() const {
    return _pIO;
}

void pCIOEditor::setObject( QSharedPointer< pIObject > pIO ) {
    _pIO = pIO;
}

void pCIOEditor::initActions() {
    QAction* actRecAdd = _tbIOActions->addAction( QIcon(":/patrol/add_parameter.svg"), tr("Create new record") );
    actRecAdd->setToolTip( tr("Create new record") );
    QKeySequence ksAdd( QKeySequence::New );//Qt::CTRL | Qt::Key_N );
    actRecAdd->setShortcut( ksAdd );
    QObject::connect( actRecAdd, &QAction::triggered, this, &pCIOEditor::addRecord );

    QAction* actRecEdit = _tbIOActions->addAction( QIcon(":/patrol/edit_parameter.svg"), tr("Edit record") );
    actRecEdit->setToolTip( tr("Edit record") );
    QKeySequence ksEdit( QKeySequence::Open );//Qt::Key_F4 );
    actRecEdit->setShortcut( ksEdit );
    QObject::connect( actRecEdit, &QAction::triggered, this, &pCIOEditor::editRecord );

    QAction* actRecDel = _tbIOActions->addAction( QIcon(":/patrol/del_parameter.svg"), tr("Delete record") );
    actRecDel->setToolTip( tr("Delete record") );
    QKeySequence ksDel( QKeySequence::Delete );
    //Qt::Key_Delete | Qt::Key_F8 );
    actRecDel->setShortcut( ksDel );
    QObject::connect( actRecDel, &QAction::triggered, this, &pCIOEditor::delRecord );
}

void pCIOEditor::addRecord() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCIOEditor::editRecord() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCIOEditor::delRecord() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCIOEditor::appendTabWidget( QWidget* w, QString title ) {
    _tabW->addTab( w, title );
}
