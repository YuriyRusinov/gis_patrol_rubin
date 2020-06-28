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

pCatGuiFactory::pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, PGUIFactory* guif, QObject* parent )
    : QObject( parent ), _dbLoader( dbLoader), _dbWriter( dbWriter ),
    _guiFactory( guif ) {
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
    QSharedPointer< pCategoryType > cType = pCTypes.value( defaultType, nullptr );
    QSharedPointer< pCategory > pCat ( new pCategory );
    pCat->setType( cType );
    pCatEditor* cEditor = new pCatEditor( pCat, pCTypes );
    QObject::connect( cEditor,
                      &pCatEditor::addParameterIntoCategory,
                      this,
                      &pCatGuiFactory::addParameterToCat
            );
    QObject::connect( cEditor,
                      &pCatEditor::removeParameterFromCategory,
                      this,
                      &pCatGuiFactory::removeParameterFromCat
            );
    pCatParametersModel* pcMod = new pCatParametersModel( pCat->categoryPars() );
    cEditor->setCatParamModel( pcMod );
    if( pCat->getTableCat().isNull() ){
        qint64 defaultTableType = 10;
        QSharedPointer< pCategory > pTableCat ( new pCategory( -2, QString(), QString(), pCTypes.value( defaultTableType, nullptr ) ) );
        pCat->setTableCat( pTableCat );
    }
    pCatParametersModel* pcTableMod = new pCatParametersModel( pCat->getTableCat()->categoryPars() );
    cEditor->setTableCatParamModel( pcTableMod );
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
    QObject::connect( cEditor,
                      &pCatEditor::addParameterIntoCategory,
                      this,
                      &pCatGuiFactory::addParameterToCat
            );
    QObject::connect( cEditor,
                      &pCatEditor::removeParameterFromCategory,
                      this,
                      &pCatGuiFactory::removeParameterFromCat
            );
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

void pCatGuiFactory::addParameterToCat( QSharedPointer< pCategory > pc, QAbstractItemModel* cAttrModel ) {
    if( pc.isNull() || cAttrModel == nullptr )
        return;
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatGuiFactory::removeParameterFromCat( QSharedPointer< pCategory > pc, qint64 idParameter, QModelIndex parIndex, QAbstractItemModel* cAttrModel ) {
    if( pc.isNull() || cAttrModel == nullptr || idParameter <= 0 || !parIndex.isValid() )
        return;
    qDebug() << __PRETTY_FUNCTION__;
}
