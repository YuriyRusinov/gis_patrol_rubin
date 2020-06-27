/*
 * @brief Класс-фабрика, управляющий визуальным отображением категорий
 * pCatGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QMessageBox>
#include <QtDebug>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pCategoryListForm.h>
#include <pCategoryModel.h>
#include <pCategory.h>
#include <pCatEditor.h>
#include <pCatParamModel.h>

#include "pCatGuiFactory.h"

pCatGuiFactory::pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent )
    : QObject( parent ), _dbLoader( dbLoader), _dbWriter( dbWriter ) {
}

pCatGuiFactory::~pCatGuiFactory() {
}

QWidget* pCatGuiFactory::GUICatView( QWidget* parent, Qt::WindowFlags flags ) {
    pCategoryListForm* pclf = new pCategoryListForm( parent, flags );
    QObject::connect( pclf, &pCategoryListForm::addCategory, this, &pCatGuiFactory::addPCategory );
    QObject::connect( pclf, &pCategoryListForm::editCategory, this, &pCatGuiFactory::editPCategory );
    QObject::connect( pclf, &pCategoryListForm::delCategory, this, &pCatGuiFactory::delPCategory );
    QObject::connect( pclf, &pCategoryListForm::refrechCatMod, this, &pCatGuiFactory::refreshCats );
    QMap< qint64, QSharedPointer< pCategory > > categories = _dbLoader->loadCategories();
    qDebug() << __PRETTY_FUNCTION__ << categories.size();
    pCategoryModel* pCatMod = new pCategoryModel( categories );
    pclf->setCatModel( pCatMod );
    return pclf;
}

void pCatGuiFactory::addPCategory( QAbstractItemModel* catMod ) {
    qDebug() << __PRETTY_FUNCTION__ << catMod;
    QMap< qint64, QSharedPointer< pCategoryType > > pCTypes = _dbLoader->loadAvailCatTypes();
    qint64 defaultType = 1;
    QSharedPointer< pCategory > pCat ( new pCategory );
    pCat->setType( pCTypes.value( defaultType, nullptr ) );
    pCatEditor* cEditor = new pCatEditor( pCat, pCTypes );
    emit viewCatWidget( cEditor );
}

void pCatGuiFactory::editPCategory( QAbstractItemModel* catMod, QSharedPointer< pCategory > pCat, QModelIndex cIndex ) {
    if (pCat.isNull()) {
        QMessageBox::warning( qobject_cast<QWidget*>(this->sender()), tr("Edit category"), tr("Cannot edit category, error"), QMessageBox::Ok );
        return;
    }
    qDebug() << __PRETTY_FUNCTION__ << catMod << pCat.isNull() << cIndex;
    QMap< qint64, QSharedPointer< pCategoryType > > pCTypes = _dbLoader->loadAvailCatTypes();
    pCatEditor* cEditor = new pCatEditor( pCat, pCTypes );
    pCatParametersModel* pcMod = new pCatParametersModel( pCat->categoryPars() );
    cEditor->setCatParamModel( pcMod );
    if( !pCat->getTableCat().isNull() ) {
        pCatParametersModel* pcTableMod = new pCatParametersModel( pCat->getTableCat()->categoryPars() );
        cEditor->setTableCatParamModel( pcTableMod );
    }
    emit viewCatWidget( cEditor );
}

void pCatGuiFactory::delPCategory( QAbstractItemModel* catMod, QModelIndex cIndex ) {
    qDebug() << __PRETTY_FUNCTION__ << catMod << cIndex;
}

void pCatGuiFactory::refreshCats() {
    qDebug() << __PRETTY_FUNCTION__;
}
