/*
 * @brief Класс-виджет для отображения записей справочника и соответствующих операций
 * pRecWidget.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAbstractItemModel>
#include <QAbstractProxyModel>
#include <QAction>
#include <QGridLayout>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QModelIndex>
#include <QToolBar>
#include <QTreeView>
#include <QtDebug>

#include "pRecWidget.h"

pRecWidget::pRecWidget( QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
    _tbRecActions( new QToolBar ),
    _tvRecords( new QTreeView ) {

    setup( );
}

pRecWidget::~pRecWidget() {
    delete _tvRecords;
    delete _tbRecActions;
}

QAbstractItemModel* pRecWidget::getSourceModel() const {
    QAbstractItemModel* wModel = _tvRecords->model();
    QAbstractProxyModel* wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel);
    for( ;wModel && wProxyModel; wModel = wProxyModel->sourceModel() ) 
        wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel);
    return wModel;
}

qint64 pRecWidget::getRecId() const {
    QItemSelectionModel* selModel = _tvRecords->selectionModel();
    if( selModel->selectedIndexes().isEmpty() )
        return -1;
    QModelIndex wIndex = selModel->selectedIndexes().at( 0 );
    QAbstractItemModel* wModel = selModel->model();
    QAbstractProxyModel* wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel);
    for(; wModel && wProxyModel; wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel) ) {
        wIndex = wProxyModel->mapToSource( wIndex );
        wModel = wProxyModel->sourceModel();
    }
    qint64 idRes = wIndex.data( Qt::UserRole ).toLongLong();
    return idRes;
}

void pRecWidget::setSourceModel( QAbstractItemModel* recModel ) {
    QAbstractItemModel* oldModel = _tvRecords->model();
    _tvRecords->setModel( recModel );
    if( oldModel && oldModel != recModel )
        delete oldModel;
}

void pRecWidget::refreshModel() {
    emit refreshRecords();
    qDebug() << __PRETTY_FUNCTION__;
}

void pRecWidget::addNewRecord() {
    QAbstractItemModel* recMod = getSourceModel();
    qDebug() << __PRETTY_FUNCTION__ << recMod;
    emit addRecord( recMod );
}

void pRecWidget::editSelectedRecord() {
    QItemSelectionModel* selModel = _tvRecords->selectionModel();
    if( selModel->selectedIndexes().isEmpty() ) {
        QMessageBox::warning( this, tr("Edit record"), tr("Select record for edit"), QMessageBox::Ok );
        return ;
    }
    QModelIndex wIndex = selModel->selectedIndexes().at( 0 );
    QAbstractItemModel* wModel = selModel->model();
    QAbstractProxyModel* wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel);
    for(; wModel && wProxyModel; wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel) ) {
        wIndex = wProxyModel->mapToSource( wIndex );
        wModel = wProxyModel->sourceModel();
    }
    qDebug() << __PRETTY_FUNCTION__ << wModel << wIndex;
    emit editRecord( wModel, wIndex );
}

void pRecWidget::delSelectedRecord() {
    QItemSelectionModel* selModel = _tvRecords->selectionModel();
    if( selModel->selectedIndexes().isEmpty() ) {
        QMessageBox::warning( this, tr("Delete record"), tr("Select record for delete"), QMessageBox::Ok );
        return ;
    }
    QModelIndex wIndex = selModel->selectedIndexes().at( 0 );
    QAbstractItemModel* wModel = selModel->model();
    QAbstractProxyModel* wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel);
    for(; wModel && wProxyModel; wProxyModel = qobject_cast<QAbstractProxyModel*>(wModel) ) {
        wIndex = wProxyModel->mapToSource( wIndex );
        wModel = wProxyModel->sourceModel();
    }
    qDebug() << __PRETTY_FUNCTION__ << wModel << wIndex;
    emit delRecord( wModel, wIndex );
}

void pRecWidget::setup( ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _tbRecActions );
    grLay->addWidget( _tvRecords );

    QAction* actRefresh = _tbRecActions->addAction( QIcon(":/patrol/refresh_parameters.svg"), tr("Refresh records") );
    actRefresh->setToolTip( tr("Refresh") );
    QKeySequence ksRefresh( QKeySequence::Refresh );
    actRefresh->setShortcut( ksRefresh );
    QObject::connect( actRefresh, &QAction::triggered, this, &pRecWidget::refreshModel );

    QAction* actRecAdd = _tbRecActions->addAction( QIcon(":/patrol/add_parameter.svg"), tr("Create new record") );
    actRecAdd->setToolTip( tr("Create new record") );
    QKeySequence ksAdd( QKeySequence::New );//Qt::CTRL | Qt::Key_N );
    actRecAdd->setShortcut( ksAdd );
    QObject::connect( actRecAdd, &QAction::triggered, this, &pRecWidget::addNewRecord );

    QAction* actRecEdit = _tbRecActions->addAction( QIcon(":/patrol/edit_parameter.svg"), tr("Edit record") );
    actRecEdit->setToolTip( tr("Edit record") );
    QKeySequence ksEdit( QKeySequence::Open );//Qt::Key_F4 );
    actRecEdit->setShortcut( ksEdit );
    QObject::connect( actRecEdit, &QAction::triggered, this, &pRecWidget::editSelectedRecord );

    QAction* actRecDel = _tbRecActions->addAction( QIcon(":/patrol/del_parameter.svg"), tr("Delete record") );
    actRecDel->setToolTip( tr("Delete record") );
    QKeySequence ksDel( QKeySequence::Delete );
    //Qt::Key_Delete | Qt::Key_F8 );
    actRecDel->setShortcut( ksDel );
    QObject::connect( actRecDel, &QAction::triggered, this, &pRecWidget::delSelectedRecord );
}
