/*
 * @brief Класс-виджет, содержащий список категорий и элементы управления им
 * pCategoryListForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QToolBar>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QItemSelection>
#include <QMessageBox>
#include <QTreeView>
#include <QAction>
#include <QGridLayout>
#include <QtDebug>

#include <pCategory.h>
#include "pCategoryListForm.h"

pCategoryListForm::pCategoryListForm( QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
    _tbCatActions( new QToolBar ),
    _tvCat( new QTreeView ) {
    QGridLayout* gLay = new QGridLayout( this );
    gLay->addWidget( _tbCatActions, 0, 0, 1, 1 );
    gLay->addWidget( _tvCat, 1, 0, 1, 1);
    init();
}

pCategoryListForm::~pCategoryListForm() {
    delete _tbCatActions;
    delete _tvCat;
}

QAbstractItemModel* pCategoryListForm::getCatModel() {
    return _tvCat->model();
}

void pCategoryListForm::setCatModel( QAbstractItemModel* cModel ) {
    QAbstractItemModel* oldModel = _tvCat->model();
    _tvCat->setModel( cModel );
    if (oldModel && oldModel != cModel)
        delete oldModel;
}

void pCategoryListForm::addcategory( ) {
    qDebug() << __PRETTY_FUNCTION__;
    QAbstractItemModel* cModel = _tvCat->model();
    emit addCategory( cModel );
}

void pCategoryListForm::editcategory( ) {
    qDebug() << __PRETTY_FUNCTION__;
    QItemSelectionModel* selModel = _tvCat->selectionModel();
    QItemSelection sel = selModel->selection();
    QAbstractItemModel* cModel = _tvCat->model();
    if ( sel.indexes().isEmpty() ) {
        QMessageBox::warning( this, tr("Edit category"), tr("Please select category for edit"), QMessageBox::Ok );
        return;
    }
    QModelIndex cIndex = sel.indexes().at( 0 );
    //
    // Мы можем редактировать только в комплексе главную и дочернюю
    // категории
    //
    if (cIndex.parent().isValid()) {
        QSharedPointer< pCategory > pChildCat = cIndex.data( Qt::UserRole+1 ).value<QSharedPointer< pCategory > >();
        qDebug() << __PRETTY_FUNCTION__ << pChildCat->getId();
        cIndex = cIndex.parent();
    }
    QSharedPointer< pCategory > pCat = cIndex.data( Qt::UserRole+1 ).value<QSharedPointer< pCategory > >();
    qDebug() << __PRETTY_FUNCTION__ << cIndex << pCat->getId();
    emit editCategory( cModel, pCat, cIndex );
}

void pCategoryListForm::delcategory( ) {
    QItemSelectionModel* selModel = _tvCat->selectionModel();
    QItemSelection sel = selModel->selection();
    QAbstractItemModel* cModel = _tvCat->model();
    if ( sel.indexes().isEmpty() ) {
        QMessageBox::warning( this, tr("Delete category"), tr("Please select category for remove"), QMessageBox::Ok );
        return;
    }
    QModelIndex cIndex = sel.indexes().at( 0 );
    if (cIndex.parent().isValid()) {
        cIndex = cIndex.parent();
    }
    QSharedPointer< pCategory > pCat = cIndex.data( Qt::UserRole+1 ).value<QSharedPointer< pCategory > >();
    QMessageBox::StandardButton qres = QMessageBox::question( this, tr("Delete category"), tr( "Do you really want to delete category %1 and its child category ?").arg( pCat->getName() ), QMessageBox::Yes | QMessageBox::No, QMessageBox::No );
    if( qres != QMessageBox::Yes )
        return;
    emit delCategory( cModel, cIndex );
    qDebug() << __PRETTY_FUNCTION__;
}

void pCategoryListForm::refreshC( ) {
    qDebug() << __PRETTY_FUNCTION__;
    emit refrechCatMod();
}

void pCategoryListForm::init() {
    QAction* actAddCat = _tbCatActions->addAction(QIcon(":/patrol/add_parameter.svg"), tr("Add category") );
    actAddCat->setToolTip( tr("Add new category") );
    QObject::connect( actAddCat, &QAction::triggered, this, &pCategoryListForm::addcategory );

    QAction* actEditCat = _tbCatActions->addAction(QIcon(":/patrol/edit_parameter.svg"), tr("Edit category") );
    actEditCat->setToolTip( tr("Edit existing category") );
    QObject::connect( actEditCat, &QAction::triggered, this, &pCategoryListForm::editcategory );

    QAction* actDelCat = _tbCatActions->addAction(QIcon(":/patrol/del_parameter.svg"), tr("Delete category") );
    actDelCat->setToolTip( tr("Delete category") );
    QObject::connect( actDelCat, &QAction::triggered, this, &pCategoryListForm::delcategory );

    QAction* actRefresh = _tbCatActions->addAction(QIcon(":/patrol/refresh_parameters.svg"), tr("Refresh") );
    actRefresh->setToolTip( tr("Refresh categories") );
    QObject::connect( actRefresh, &QAction::triggered, this, &pCategoryListForm::refreshC );
}
