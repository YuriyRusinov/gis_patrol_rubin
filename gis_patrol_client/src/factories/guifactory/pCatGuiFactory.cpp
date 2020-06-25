/*
 * @brief Класс-фабрика, управляющий визуальным отображением категорий
 * pCatGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pCategoryListForm.h>
#include <pCategoryModel.h>
#include <pCategory.h>
#include <pCatEditor.h>

#include "pCatGuiFactory.h"

pCatGuiFactory::pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent )
    : QObject( parent ), _dbLoader( dbLoader), _dbWriter( dbWriter ) {
}

pCatGuiFactory::~pCatGuiFactory() {
}

QWidget* pCatGuiFactory::GUICatView( QWidget* parent, Qt::WindowFlags flags ) {
    pCategoryListForm* pclf = new pCategoryListForm( parent, flags );
    QMap< qint64, QSharedPointer< pCategory > > categories = _dbLoader->loadCategories();
    qDebug() << __PRETTY_FUNCTION__ << categories.size();
    return pclf;
}

void pCatGuiFactory::addPCategory( QAbstractItemModel* catMod ) {
    qDebug() << __PRETTY_FUNCTION__ << catMod;
    pCatEditor* cEditor = new pCatEditor();
    emit viewCatWidget( cEditor );
}

void pCatGuiFactory::editPCategory( QAbstractItemModel* catMod, QSharedPointer< pCategory > pCat, QModelIndex cIndex ) {
    qDebug() << __PRETTY_FUNCTION__ << catMod << pCat.isNull() << cIndex;
    pCatEditor* cEditor = new pCatEditor();
    emit viewCatWidget( cEditor );
}

void pCatGuiFactory::delPCategory( QAbstractItemModel* catMod, QModelIndex cIndex ) {
    qDebug() << __PRETTY_FUNCTION__ << catMod << cIndex;
}

void pCatGuiFactory::refreshCats() {
    qDebug() << __PRETTY_FUNCTION__;
}
