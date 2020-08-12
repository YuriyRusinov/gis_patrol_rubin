/*
 * @brief Класс-фабрика, управляющий визуальным отображением категорий
 * pCatGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QDialog>
#include <QMessageBox>
#include <QVector>
#include <QtDebug>

#include <defines.h>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pCategoryListForm.h>
#include <pCategoryModel.h>
#include <pCategory.h>
#include <pCatEditor.h>
#include <pCatParamModel.h>
#include <pParameter.h>
#include <pCatParameter.h>
#include <pParamListForm.h>

#include "pParamGuiFactory.h"
#include "pCatGuiFactory.h"

pCatGuiFactory::pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, pParamGUIFactory* guif, QObject* parent )
    : pEntityFactory( parent ), _dbLoader( dbLoader), _dbWriter( dbWriter ),
    _guiFactory( guif ) {
}

pCatGuiFactory::~pCatGuiFactory() {
}

QWidget* pCatGuiFactory::GUIView( QWidget* parent, Qt::WindowFlags flags ) {
    pCategoryListForm* pclf = new pCategoryListForm( parent, flags );
    QObject::connect( pclf, &pCategoryListForm::addCategory, this, &pCatGuiFactory::addPCategory );
    QObject::connect( pclf, &pCategoryListForm::editCategory, this, &pCatGuiFactory::editPCategory );
    QObject::connect( pclf, &pCategoryListForm::delCategory, this, &pCatGuiFactory::delPCategory );
    QObject::connect( pclf, &pCategoryListForm::refrechCatMod, this, &pCatGuiFactory::refreshCats );
    QMap< qint64, QSharedPointer< pCategory > > categories = _dbLoader->loadCategories();
    qDebug() << __PRETTY_FUNCTION__ << categories.size();
    pCategoryModel* pCatMod = new pCategoryModel( categories );
    pclf->setCatModel( pCatMod );
    emit viewWidget( pclf );
    return pclf;
}

QWidget* pCatGuiFactory::GUICategoryEditor( QSharedPointer< pCategory > pCat, QWidget* parent, Qt::WindowFlags flags ) {
    QMap< qint64, QSharedPointer< pCategoryType > > pCTypes = _dbLoader->loadAvailCatTypes();
    qint64 defaultType = 1;
    QSharedPointer< pCategoryType > cType = pCTypes.value( defaultType, nullptr );
    pCat->setType( cType );
    pCatEditor* cEditor = new pCatEditor( pCat, pCTypes, parent, flags );
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
    QObject::connect( cEditor,
                      &pCatEditor::saveCat,
                      this,
                      &pCatGuiFactory::saveCategory
            );
    pCatParametersModel* pcMod = new pCatParametersModel( pCat->categoryPars() );
    cEditor->setCatParamModel( pcMod );
    if( !pCat->getTableCat().isNull() ) {
        pCatParametersModel* pcTableMod = new pCatParametersModel( pCat->getTableCat()->categoryPars() );
        cEditor->setTableCatParamModel( pcTableMod );
    }
    return cEditor;
}

void pCatGuiFactory::addPCategory( ) {
    QMap< qint64, QSharedPointer< pCategoryType > > pCTypes = _dbLoader->loadAvailCatTypes();
    qint64 defaultType = 1;
    QSharedPointer< pCategoryType > cType = pCTypes.value( defaultType, nullptr );
    QSharedPointer< pCategory > pCat ( new pCategory );
    pCat->setType( cType );
    if( pCat->getTableCat().isNull() ){
        qint64 defaultTableType = 10;
        QSharedPointer< pCategory > pTableCat ( new pCategory( -2, QString(), QString(), pCTypes.value( defaultTableType, nullptr ) ) );
        pCat->setTableCat( pTableCat );
    }
    pCatEditor* cEditor = qobject_cast<pCatEditor*>(GUICategoryEditor( pCat ));
    emit viewWidget( cEditor );
}

void pCatGuiFactory::editPCategory( QAbstractItemModel* catMod, QSharedPointer< pCategory > pCat, QModelIndex cIndex ) {
    if (pCat.isNull()) {
        QMessageBox::warning( qobject_cast<QWidget*>(this->sender()), tr("Edit category"), tr("Cannot edit category, error"), QMessageBox::Ok );
        return;
    }
    qDebug() << __PRETTY_FUNCTION__ << catMod << pCat.isNull() << cIndex;
    QMap< qint64, QSharedPointer< pCategoryType > > pCTypes = _dbLoader->loadAvailCatTypes();
    pCatEditor* cEditor = qobject_cast<pCatEditor*>(GUICategoryEditor( pCat ));
    emit viewWidget( cEditor );
}

void pCatGuiFactory::delPCategory( QAbstractItemModel* catMod, QModelIndex cIndex ) {
    qDebug() << __PRETTY_FUNCTION__ << catMod << cIndex;
    if( catMod == nullptr || !cIndex.isValid() )
        return;
    qint64 idCat = cIndex.data( Qt::UserRole ).toLongLong();
    qint64 res = _dbWriter->deleteCategory( idCat );
    if ( res < 0 ) {
        QMessageBox::warning( qobject_cast<QWidget*>(this->sender()), tr("Delete category"), tr("Cannot delete category %1").arg( idCat ), QMessageBox::Ok );
        return;
    }
    int iRow = cIndex.row();
    catMod->removeRows( iRow, 1, cIndex.parent() );
}

void pCatGuiFactory::refreshCats() {
    pCategoryListForm* pclf = qobject_cast< pCategoryListForm* >(this->sender());
    if( pclf == nullptr )
        return;
    qDebug() << __PRETTY_FUNCTION__;
    QMap< qint64, QSharedPointer< pCategory > > categories = _dbLoader->loadCategories();
    qDebug() << __PRETTY_FUNCTION__ << categories.size();
    pCategoryModel* pCatMod = new pCategoryModel( categories );
    pclf->setCatModel( pCatMod );
}

void pCatGuiFactory::addParameterToCat( QSharedPointer< pCategory > pc, QAbstractItemModel* cAttrModel ) {
    if( pc.isNull() || cAttrModel == nullptr )
        return;
    qDebug() << __PRETTY_FUNCTION__;
    QWidget* paramForm = _guiFactory->GUIViewParams( true );
    ParamListForm* paramDialog = qobject_cast< ParamListForm* >( paramForm );
    if (!paramDialog || paramDialog->exec() != QDialog::Accepted )
        return;
    QMap< qint64, QSharedPointer< pParameter > > params = paramDialog->getParameters();
    int npars (pc->categoryPars().size());
    int nr = cAttrModel->rowCount();
    int iorder = 0;
    qDebug() << __PRETTY_FUNCTION__ << nr << npars << params.size();
    bool isInserted = cAttrModel->insertRows(nr, params.size());
    for ( QMap< qint64, QSharedPointer< pParameter > >::const_iterator ppc = params.constBegin();
            ppc != params.constEnd();
            ppc++ ) {
        QSharedPointer< pCatParameter > pcp ( new pCatParameter ( (*ppc.value()), false, false, QVariant(), npars+iorder+1 ) );
        pc->addParam( ppc.key(), pcp );
        QModelIndex pcIndex = cAttrModel->index( nr+iorder, 0 );
        iorder++;
        qDebug() << __PRETTY_FUNCTION__ << isInserted << pcIndex;
        cAttrModel->setData( pcIndex, QVariant::fromValue< QSharedPointer< pCatParameter > >( pcp ), Qt::UserRole+1 );
    }
}

void pCatGuiFactory::removeParameterFromCat( QSharedPointer< pCategory > pc, qint64 idParameter, QModelIndex parIndex, QAbstractItemModel* cAttrModel ) {
    if( pc.isNull() || cAttrModel == nullptr || idParameter <= 0 || !parIndex.isValid() )
        return;
    int pOrder = parIndex.data( Qt::UserRole+2 ).toInt();
    int iRow = parIndex.row();
    cAttrModel->removeRows( iRow, 1, parIndex.parent() );
    pc->removeParam( idParameter );
    QVector< qint64 > lpars;
    for( QMap< qint64, QSharedPointer< pCatParameter >>::const_iterator pcp= pc->categoryPars().constBegin(); pcp != pc->categoryPars().constEnd(); pcp++) {
        qDebug() << __PRETTY_FUNCTION__ << pcp.value()->paramOrder();
    }
    findCatParamsByOrder( lpars, pc->categoryPars(), pOrder );
    qDebug() << __PRETTY_FUNCTION__ << pOrder << idParameter << lpars;
/*
 *  Отладочная печать приоритетов
    int nl = lpars.size();
    for( int i=0; i<nl; i++) {
        QSharedPointer< pCatParameter > pca = pc->categoryPars().value( lpars[i] );
        qDebug() << __PRETTY_FUNCTION__ << lpars[i] << pca->paramOrder();
        pca->paramOrder()--;
        QModelIndex wInd = cAttrModel->index( iRow+i, 0, parIndex.parent() );
        cAttrModel->setData( wInd, pca->paramOrder(), Qt::UserRole+2 );
    }
*/
}

void pCatGuiFactory::saveCategory( QSharedPointer< pCategory > pCategory ) {
    if( pCategory.isNull() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << pCategory->getId() << (pCategory->getTableCat().isNull() ? QString("Not reference") : QString::number(pCategory->getTableCat()->getId()));
    qint64 idCategory ( -1 );
    if( pCategory->getId() <= 0 ) {
        if( pCategory->getTableCat() && !pCategory->getTableCat()->categoryPars().contains( 1 ) ) {
            QMessageBox::StandardButton res = QMessageBox::question(qobject_cast<QWidget*>(this->sender()), tr("Create/edit category"), tr("Table category does not contains ID. Do you want to add it ?"), QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No), QMessageBox::Yes);
            if (res == QMessageBox::Yes) {
                QSharedPointer< pParameter > pId = _dbLoader->loadParameter( ATTR_ID );
                QSharedPointer< pCatParameter> pcId ( new pCatParameter( *pId, false, false, QVariant(), 1 ) );
                pCategory->getTableCat()->addParam( ATTR_ID, pcId );
                for( QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pca= pCategory->getTableCat()->categoryPars().constBegin();
                        pca != pCategory->getTableCat()->categoryPars().constEnd();
                        pca++ ) {
                    if( pca.key() == ATTR_ID )
                        continue;
                    pca.value()->paramOrder()++;
                }

            }
            else
                return;
        }
        if( !pCategory->getTableCat().isNull() )
            for( QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pca= pCategory->getTableCat()->categoryPars().constBegin();
                    pca != pCategory->getTableCat()->categoryPars().constEnd();
                    pca++ ) {
                qDebug() << __PRETTY_FUNCTION__ << pca.value()->getCode() << pca.value()->paramOrder();
            }
        idCategory = _dbWriter->writeCategory( pCategory );
        qDebug() << __PRETTY_FUNCTION__ << "Category was saved";
    }
    else
        idCategory = _dbWriter->updateCategory( pCategory );

    if( idCategory < 0 ) {
        QMessageBox::warning( qobject_cast<QWidget*>(this->sender()), tr("Create/edit category"), tr("Cannot write category, DB Error"), QMessageBox::Ok );
        return;
    }
}

void pCatGuiFactory::createCategory( QSharedPointer< pCategory > pCat, QWidget* parent, Qt::WindowFlags flags ) {
    QMap< qint64, QSharedPointer< pCategoryType > > pCTypes = _dbLoader->loadAvailCatTypes();
    qint64 defaultType = 1;
    QSharedPointer< pCategoryType > cType = pCTypes.value( defaultType, nullptr );
    pCat.reset ( new pCategory );
    pCat->setType( cType );
    if( pCat->getTableCat().isNull() ){
        qint64 defaultTableType = 10;
        QSharedPointer< pCategory > pTableCat ( new pCategory( -2, QString(), QString(), pCTypes.value( defaultTableType, nullptr ) ) );
        pCat->setTableCat( pTableCat );
    }
    pCatEditor* cEditor = qobject_cast<pCatEditor*>(GUICategoryEditor( pCat, parent, flags ));
    emit viewWidget( cEditor );
}
