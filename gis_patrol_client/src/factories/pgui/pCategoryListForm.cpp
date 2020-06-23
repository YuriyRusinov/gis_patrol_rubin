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
}

void pCategoryListForm::editcategory( ) {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCategoryListForm::delcategory( ) {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCategoryListForm::refreshC( ) {
    qDebug() << __PRETTY_FUNCTION__;
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
