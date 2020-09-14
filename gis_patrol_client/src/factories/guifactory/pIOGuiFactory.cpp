/*
 * @brief Класс-фабрика для информационных объектов и записей
 * pIOGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAbstractItemView>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTreeView>
#include <QWidget>
#include <QtDebug>

#include <defines.h>
#include <pAbstractParamWidget.h>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pIObject.h>
#include <pRecord.h>
#include <pRecordC.h>
#include <pCategory.h>
#include <pCatParameter.h>
#include <pParamValue.h>
#include <pCIOEditor.h>
#include <pRefLineEdit.h>
#include <pRecordDataModel.h>
#include <precdialog.h>
#include <pCategoryModel.h>
#include <pRecWidget.h>
#include <psearchform.h>

#include "pParamGuiFactory.h"
#include "pCatGuiFactory.h"
#include "pIOGuiFactory.h"

QWidget* pIOGuiFactory::GUIView( QWidget* parent, Qt::WindowFlags flags ) {
    QSharedPointer< pIObject > pIO = _dbLoader->loadIO( IO_IO_ID );
    QSharedPointer< pRecordCopy > pRec = _dbLoader->loadCopy( IO_IO_ID, pIO );
    if (pIO.isNull() || pRec.isNull() )
        return nullptr;

    QSharedPointer< pCategory > pCat = pIO->getCategory();
    QList< QSharedPointer< pParamValue > > paramValues;
    pCIOEditor* wEditor = createRecEditor ( pCat, pIO, pRec, paramValues, parent, flags );
    emit viewWidget( wEditor );
    return wEditor;
}

pIOGuiFactory::pIOGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, pParamGUIFactory* paramF, pCatGuiFactory* catF, QObject* parent )
    : pEntityFactory( parent ),
    _dbLoader( dbLoader ),
    _dbWriter( dbWriter ),
    _paramFactory( paramF ),
    _catFactory( catF ) {
}

pIOGuiFactory::~pIOGuiFactory( ) {}

QWidget* pIOGuiFactory::viewRecParams( QSharedPointer< pCategory > pCategory, QSharedPointer< pRecordCopy > pRec, pCIOEditor* editor, QList< QSharedPointer< pParamValue > > paramValues, QWidget* parent, Qt::WindowFlags flags ) const {
    if( pCategory.isNull() || pRec.isNull() )
        return nullptr;
    QMap<int, QSharedPointer< pCatParameter > > sortedParams;
    QMap<qint64, QSharedPointer< pCatParameter > > cpars = pCategory->categoryPars();
    if( cpars.size() == 0 )
        return nullptr;
    for(QMap<qint64, QSharedPointer< pCatParameter > >::const_iterator pca = cpars.constBegin();
            pca != cpars.constEnd();
            pca++ )
        sortedParams.insert( pca.value()->getOrder(), pca.value() );
    QWidget* paramWidget = new QWidget( parent, flags );
    QGridLayout* grLay = new QGridLayout( paramWidget );
    int i=0;
    for(QMap<int, QSharedPointer< pCatParameter > >::const_iterator pca = sortedParams.constBegin();
        pca != sortedParams.constEnd();
        pca++ ) {
        QSharedPointer< pParamValue > pval ( nullptr );
        int iValNum = searchValue(paramValues, pca.value());
        bool readOnlyVal = false;
        if( pRec->paramValue( pca.value()->getId() ).isNull() ) {
            //
            // Something incorrect, debug output
            //
            qDebug() << __PRETTY_FUNCTION__ << QString("Null parameter %1 in record, category is %2").arg( pca.value()->getCode() ).arg ( pCategory->getId() );
            continue;
        }
        else if( pRec->getId() < 0 && iValNum >= 0 ) {
            pval = QSharedPointer< pParamValue >( pRec->paramValue( pca.value()->getId() ));
            pval->setValue( paramValues[iValNum]->value() );
            pval->setColumnValue( paramValues[iValNum]->getColumnValue() );
            qDebug() << __PRETTY_FUNCTION__ << paramValues[iValNum]->value();
            readOnlyVal = true;
        }
        else if( pRec->getId() < 0 && pca.value()->getId() == ATTR_AUTHOR ) {
            pval = QSharedPointer< pParamValue >( pRec->paramValue( pca.value()->getId() ));
            qint64 idUser = _dbLoader->getCurrentUser();
            QSharedPointer< pIObject > pAuthors = _dbLoader->loadIO( IO_USERS_ID );
            QSharedPointer< pRecordCopy > rcUser = _dbLoader->loadCopy( idUser, pAuthors );
            pval->setValue( idUser );
            pval->setColumnValue( rcUser->paramValue( ATTR_FIO )->value().toString() );
            qDebug() << __PRETTY_FUNCTION__ << tr("Author is %1 %2").arg(idUser).arg( rcUser->paramValue( ATTR_FIO )->value().toString() );
            readOnlyVal = true;
        }
        else
            pval = QSharedPointer< pParamValue >( pRec->paramValue( pca.value()->getId() ));
        pAbstractParamWidget* pw = _paramFactory->createParamWidget( pval, paramWidget );
        readOnlyVal = readOnlyVal || (pca.value()->isReadOnly() && pRec->getId() > 0);
        //qDebug() << __PRETTY_FUNCTION__ << pca.value()->getId() << pval.isNull() << (pw == nullptr ) << pca.value()->getParamType()->getId() << readOnlyVal;
        if( pw != nullptr ) {
            pw->setReadOnly( readOnlyVal );
            grLay->addWidget( pw, i, 0, 1, 1 );
            QObject::connect( pw, &pAbstractParamWidget::valueChanged, editor, &pCIOEditor::slotParamRecChanged );
            i++;
        }
        if( qobject_cast<pRefLineEdit*>(pw) ) {
            pRefLineEdit* pRefLE = qobject_cast<pRefLineEdit*>(pw);
            QObject::connect( pRefLE, &pRefLineEdit::changeRecord, editor, &pCIOEditor::slotChangeReference );
        }
    }
    return paramWidget;
}

void pIOGuiFactory::loadParamRef( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pParamValue > pValue, QString tableName, QString columnName, QLineEdit* lE ) {
    qDebug() << pValue.isNull() << pValue->getCatParam().isNull() << columnName;
    if( pValue.isNull() || pValue->getCatParam().isNull() || columnName.isEmpty() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << tableName;
    QSharedPointer< pIObject > pRefIO = _dbLoader->loadIOByTableName( tableName );
    if( pRefIO.isNull() ) {
        QWidget* pw = qobject_cast<QWidget *>(this->sender());
        QMessageBox::warning( pw, tr("Reference"), tr("Cannot load reference, error in DB"), QMessageBox::Ok );
        return;
    }
    QMap< qint64, QSharedPointer< pRecordCopy > > ioRecords = _dbLoader->loadRecords( pRefIO );
    QSharedPointer< const pCategory > pCat = pRefIO->getCategory();
    qDebug() << __PRETTY_FUNCTION__ << pRefIO->getId() << pCat->getId() << pCat->getTableCat()->getId();
    QAbstractItemModel* recModel = nullptr;
    if( pRefIO->getId() == IO_CAT_ID ) {
        //
        // Наряду с моделью общего вида у нас есть несколько частных моделей
        // для отображения параметров, имеет смысл их задействовать
        //
        QMap< qint64, QSharedPointer< pCategory > > categories = _dbLoader->loadCategories();
        recModel = new pCategoryModel( categories );
    }
    else
        recModel = new pRecordDataModel( pCat->getTableCat(), ioRecords );
    pRecDialog* pRecF = new pRecDialog;
    pRecF->setRecModel( recModel );
    if( pRecF == nullptr || pRecF->exec() != QDialog::Accepted ) {
        if( pRecF )
            delete pRecF;
        return;
    }
    qint64 idRec = pRecF->getRecId();
    QSharedPointer< pParamValue > pVal = _dbLoader->loadRecParamValue( idRec, pValue->getCatParam(), pRefIO );
    qDebug() << __PRETTY_FUNCTION__ << idRec << pVal->value();
    pValue->setValue( QVariant( idRec ) );
    QString cVal = pVal->getColumnValue();
    pValue->setColumnValue( cVal );
    delete pRecF;
    lE->setText( cVal );
    pRec->paramValue( pValue->getCatParam()->getId() )->setValue( QVariant( idRec ) );
}

void pIOGuiFactory::saveRecToDb( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pIO ) {
    if( pRec.isNull() || pIO.isNull() )
        return;
    int res = 0;
    if( pRec->getId() < 0 )
        res = _dbWriter->insertRecord( pRec, pIO );
    else
        res = _dbWriter->updateRecord( pRec, pIO );

    if( res < 0 ) {
        QWidget* w = qobject_cast<QWidget*>( this->sender() );
        QMessageBox::warning( w, tr("Save record"), tr("Save record %1, DB error code %2").arg( pRec->getId() ).arg( res ), QMessageBox::Ok );
    }
}

void pIOGuiFactory::saveIORecToDb( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pIO ) {
    if( pRec.isNull() || pIO.isNull() )
        return;
    int res( 0 );
    if( pRec->getId() < 0 ) {
        res = _dbWriter->insertRecord( pRec, pIO );
    }
    else if( pRec->getId() >= 0 && pIO->getId() == IO_IO_ID ) {
        res = _dbWriter->updateRecord( pRec, pIO );
    }
    else {
        qDebug() << __PRETTY_FUNCTION__ << pRec->getId() << pIO->getId();
        QSharedPointer< pIObject > pRecordIO = _dbLoader->loadIO( IO_IO_ID );
        res = _dbWriter->updateIORec( pRec, pIO, pRecordIO );
    }
    if( res < 0 ) {
        QWidget* w = qobject_cast<QWidget*>( this->sender() );
        QMessageBox::warning( w, tr("Save record"), tr("Save record %1, DB error code %2").arg( pRec->getId() ).arg( res ), QMessageBox::Ok );
    }
}

pRecWidget* pIOGuiFactory::createRecordsWidget( QSharedPointer< pIObject > pRefIO, QWidget* parent, Qt::WindowFlags flags ) const {
    if( pRefIO.isNull() )
        return nullptr;
    QSharedPointer< pCategory > pCat = pRefIO->getCategory();
    if( pCat.isNull() || pCat->getTableCat().isNull() )
        return nullptr;

    QMap< qint64, QSharedPointer< pRecordCopy > > ioRecords = _dbLoader->loadRecords( pRefIO );
    pRecWidget* recWidget = new pRecWidget( parent, flags );
    QAbstractItemModel* recModel = new pRecordDataModel( pCat->getTableCat(), ioRecords );
    recWidget->setSourceModel( recModel );
    pCIOEditor* wEditor = qobject_cast< pCIOEditor*> (parent);
    if( wEditor ) {
        QObject::connect( recWidget, &pRecWidget::refreshRecords, wEditor, &pCIOEditor::refreshRecords );
        QObject::connect( recWidget, &pRecWidget::searchRecordsDb, wEditor, &pCIOEditor::searchDbRecords );
        QObject::connect( recWidget, &pRecWidget::addRecord, wEditor, &pCIOEditor::createNewRecord );
        QObject::connect( recWidget, &pRecWidget::editRecord, wEditor, &pCIOEditor::editSelRecord );
        QObject::connect( recWidget, &pRecWidget::delRecord, wEditor, &pCIOEditor::delSelRecord );
    }

    return recWidget;
}

void pIOGuiFactory::createNewRec( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel ) {
    qDebug() << __PRETTY_FUNCTION__ << pRec.isNull() << pRefIO.isNull() << (recModel == nullptr);
    if( pRec.isNull() || pRefIO.isNull() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << pRec->getIO()->getId() << pRec->getId() << pRefIO->getId();
    QSharedPointer< pCategory > pCat = nullptr;//pRec->getIO()->getCategory();
    QSharedPointer< pIObject > pRecordIO = nullptr;
    if( pRec->getId() < 0 && pRec->getIO()->getId() == IO_IO_ID ) {
        pCat = pRec->getIO()->getCategory();
        pRecordIO = pRec->getIO();
    }
    else if( pRec->getId() > 0 && pRec->getIO()->getId() == IO_IO_ID ) {
        QSharedPointer< pIObject > pRecordIO_w = _dbLoader->loadIO( pRec->getId() );
        pCat = pRecordIO_w->getCategory();
        qDebug() << __PRETTY_FUNCTION__ << pCat.isNull();
        pRecordIO = pRec->getIO();
    }
    else {
        pCat = pRec->getIO()->getCategory();
        pRecordIO = pRec->getIO();
    }
    pCIOEditor* wEditor = createRecEditor( pCat, pRecordIO, pRec );
    emit viewWidget( wEditor );
}

void pIOGuiFactory::openRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex ) {
    qDebug() << __PRETTY_FUNCTION__ << pRec.isNull() << pRefIO.isNull() << (recModel == nullptr) << recIndex.isValid();
    if( pRec.isNull() || pRefIO.isNull() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << pRec->getIO()->getId() << pRec->getId();
    QSharedPointer< pCategory > pCat( pRefIO->getCategory() );
    QSharedPointer< pIObject > pRecordIO ( pRefIO );
    pCIOEditor* wEditor = createRecEditor( pCat, pRecordIO, pRec );
    emit viewWidget( wEditor );
}

void pIOGuiFactory::removeRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex ) {
    if( pRec.isNull() || pRefIO.isNull() || (recModel == nullptr) || !recIndex.isValid() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << pRefIO->getId() << pRec->getIO()->getId() << pRec->getId();
    qint64 res = _dbWriter->deleteRecord( pRec, pRefIO );
    if( res < 0 ) {
        QWidget* pw = qobject_cast<QWidget*>(this->sender());
        QMessageBox::warning(pw, tr("Delete record"), tr("Cannot delete record with id %1").arg( pRec->getId() ), QMessageBox::Ok );
        return;
    }
}

pCIOEditor* pIOGuiFactory::createRecEditor( QSharedPointer< pCategory > pRecCategory, QSharedPointer< pIObject > pRefIO, QSharedPointer< pRecordCopy > pRec, QList< QSharedPointer< pParamValue > > paramValues, QWidget* parent, Qt::WindowFlags flags ) const {
    if( pRecCategory.isNull() || pRefIO.isNull() || pRec.isNull() )
        return nullptr;

    QSharedPointer< pIObject > pRecordIO = nullptr;
    QSharedPointer< pCategory > pRecCat = nullptr;
    bool isIO = false;
    if( pRefIO->getId() == IO_IO_ID && pRec->getId() > 0 ) {
        qDebug() << __PRETTY_FUNCTION__ << pRec->getId() << pRefIO->getId();
        isIO = true;
        pRecordIO = _dbLoader->loadIO( pRec->getId() );
        pRecCat = pRecordIO->getCategory();
//        pRecordIO = pRefIO;
    }
    else {
        pRecordIO = pRefIO;
        pRecCat = pRecCategory;
    }
    isIO = isIO || pRefIO->getId() == IO_IO_ID;
    qDebug() << __PRETTY_FUNCTION__ << isIO;

    pCIOEditor* wEditor = new pCIOEditor( pRecCat, pRec, pRecordIO, isIO, parent, flags );
    QObject::connect( wEditor,
                      &pCIOEditor::loadReferenceRecords,
                      this,
                      &pIOGuiFactory::loadParamRef
            );
    QObject::connect( wEditor,
                      &pCIOEditor::saveRecord,
                      this,
                      &pIOGuiFactory::saveRecToDb
            );
    QObject::connect( wEditor,
                      &pCIOEditor::saveRecordIO,
                      this,
                      &pIOGuiFactory::saveIORecToDb
            );
    QObject::connect( wEditor,
                      &pCIOEditor::createRecord,
                      this,
                      &pIOGuiFactory::createNewRec
            );
    QObject::connect( wEditor,
                      &pCIOEditor::openRecord,
                      this,
                      &pIOGuiFactory::openRecord
            );
    QObject::connect( wEditor,
                      &pCIOEditor::delRecord,
                      this,
                      &pIOGuiFactory::removeRecord
            );
    QObject::connect( wEditor,
                      &pCIOEditor::refreshRecordModel,
                      this,
                      &pIOGuiFactory::refreshRecModel
            );
    QObject::connect( wEditor,
                      &pCIOEditor::searchRecords,
                      this,
                      &pIOGuiFactory::searchIORecords
            );

    if( pRec->getId() < 0 ) {
        QList< QSharedPointer< pParamValue > > pVals;
        QSharedPointer< pCategory > pTabC = pRecCategory->getTableCat();
        for (QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pca = pTabC->categoryPars().constBegin();
                pca != pTabC->categoryPars().constEnd();
                pca++ ) {
            QSharedPointer< pParamValue > pValue( new pParamValue( pca.value(), pca.value()->getDefaultValue() ) );
            pVals.append( pValue );
        }
        pRec->setParamValues( pVals );
    }
    QWidget* parWidget = viewRecParams( pRecCategory->getTableCat(), pRec, wEditor, paramValues );
    if( parWidget )
        wEditor->appendTabWidget( parWidget, tr("System properties") );

    QSharedPointer< pIObject > pRecIO ( nullptr );
    if( pRefIO->getId() == IO_IO_ID && pRec->getIO()->getId() == IO_IO_ID ) {
        pRecIO = _dbLoader->loadIO( pRec->getId() );
        qDebug() << __PRETTY_FUNCTION__ << (pRecIO.isNull() || pRecIO->getCategory().isNull() );
        QWidget* userParamWidget = pRecIO.isNull() ? nullptr : viewRecIOParams( pRecIO->getCategory(), pRecIO, wEditor );
        if( userParamWidget )
            wEditor->appendTabWidget( userParamWidget, tr("User properties") );
        QMap< qint64, QSharedPointer< pRecordCopy > > ioRecords = _dbLoader->loadRecords( pRecIO );
        pRecWidget* recWidget = createRecordsWidget( pRecIO, wEditor );
        wEditor->appendTabWidget( recWidget, tr("Records") );
    }
    if( wEditor->getTabCount() > 1 )
        wEditor->setCurrentPage( 1 );
    return wEditor;
}

void pIOGuiFactory::refreshRecModel( QSharedPointer< pCategory > pCat, QSharedPointer< pIObject > pRefIO, QAbstractItemView* recView ) {
    if( pCat.isNull() || pRefIO.isNull() || recView == nullptr )
        return;

    QMap< qint64, QSharedPointer< pRecordCopy > > ioRecords = _dbLoader->loadRecords( pRefIO );
    QAbstractItemModel* recModel = new pRecordDataModel( pCat->getTableCat(), ioRecords );
    QAbstractItemModel* oldModel = recView->model();
    recView->setModel( recModel );
    if( oldModel )
        delete oldModel;
}

void pIOGuiFactory::createRecordCatEditor( ) {
    QSharedPointer< pCategory > refCat = _catFactory->GUISelectCategory();
    if( refCat.isNull() )
        return;
    QSharedPointer< pParameter > pCategParam = _dbLoader->loadParameter( ATTR_ID_IO_CATEGORY );
    QSharedPointer< pCatParameter > pCategoryP( new pCatParameter( *(pCategParam.get() ) ) );
    QSharedPointer< pParamValue > pCategoryVal( new pParamValue( pCategoryP, QVariant( refCat->getId() ) ) );
    pCategoryVal->setColumnValue( refCat->getName() );
    QList< QSharedPointer< pParamValue > > pValues;
    pValues.append( pCategoryVal );
    QSharedPointer< pIObject > pIO = _dbLoader->loadIO( IO_IO_ID );
    QSharedPointer< pRecordCopy > pRec( new pRecordCopy( -1, QString(), pIO ) );//= dbl->loadCopy( IO_IO_ID, pIO );
    QSharedPointer< pCategory > pCat = pIO->getCategory();
    pCIOEditor * pRefW = this->createRecEditor( pCat, pIO, pRec, pValues );
    emit viewWidget( pRefW );
}

QWidget* pIOGuiFactory::viewRecIOParams( QSharedPointer< pCategory > pCategory, QSharedPointer< pIObject > pIORec, pCIOEditor* editor, QList< QSharedPointer< pParamValue > > paramValues, QWidget* parent, Qt::WindowFlags flags ) const {
    if( pIORec.isNull() || pCategory.isNull() || pIORec->getCategory().isNull() )
        return nullptr;
    int nparams = pIORec->paramValues().size();
    qDebug() << __PRETTY_FUNCTION__ << nparams;
    for( int i=0; i<nparams; i++) {
        qDebug() << __PRETTY_FUNCTION__ << pIORec->paramValues().at(i)->getCatParam()->getId() << pIORec->paramValues().at(i)->getCatParam()->getCode();
    }
    QMap<int, QSharedPointer< pCatParameter > > sortedParams;
    QMap<qint64, QSharedPointer< pCatParameter > > cpars = pCategory->categoryPars();
    if( cpars.size() == 0 )
        return nullptr;
    for(QMap<qint64, QSharedPointer< pCatParameter > >::const_iterator pca = cpars.constBegin();
            pca != cpars.constEnd();
            pca++ )
        sortedParams.insert( pca.value()->getOrder(), pca.value() );
    QWidget* paramWidget = new QWidget( parent, flags );
    QGridLayout* grLay = new QGridLayout( paramWidget );
    int i=0;
    for(QMap<int, QSharedPointer< pCatParameter > >::const_iterator pca = sortedParams.constBegin();
        pca != sortedParams.constEnd();
        pca++ ) {
        QSharedPointer< pParamValue > pval ( nullptr );
        int iValNum = searchValue(paramValues, pca.value());
        bool readOnlyVal = false;
        if( pIORec->paramValue( pca.value()->getId() ).isNull() ) {
            //
            // Something incorrect, debug output
            //
            qDebug() << __PRETTY_FUNCTION__ << QString("Null parameter %1 in record, category is %2").arg( pca.value()->getCode() ).arg ( pCategory->getId() );
            continue;
        }
        else if( pIORec->getId() < 0 && iValNum >= 0 ) {
            pval = QSharedPointer< pParamValue >( pIORec->paramValue( pca.value()->getId() ));
            if( pval.isNull() )
                continue;
            pval->setValue( paramValues[iValNum]->value() );
            pval->setColumnValue( paramValues[iValNum]->getColumnValue() );
            qDebug() << __PRETTY_FUNCTION__ << paramValues[iValNum]->value();
            readOnlyVal = true;
        }
        else {
            pval = QSharedPointer< pParamValue >( pIORec->paramValue( pca.value()->getId() ));
            qDebug() << __PRETTY_FUNCTION__ << pval.isNull();
        }
        pAbstractParamWidget* pw = _paramFactory->createParamWidget( pval, paramWidget );
        readOnlyVal = readOnlyVal || (pca.value()->isReadOnly() && pIORec->getId() > 0);
        //qDebug() << __PRETTY_FUNCTION__ << pca.value()->getId() << pval.isNull() << (pw == nullptr ) << pca.value()->getParamType()->getId() << readOnlyVal;
        if( pw != nullptr ) {
            pw->setReadOnly( readOnlyVal );
            grLay->addWidget( pw, i, 0, 1, 1 );
            QObject::connect( pw, &pAbstractParamWidget::valueChanged, editor, &pCIOEditor::slotParamIORecChanged );
            i++;
        }
        if( qobject_cast<pRefLineEdit*>(pw) ) {
            pRefLineEdit* pRefLE = qobject_cast<pRefLineEdit*>(pw);
            QObject::connect( pRefLE, &pRefLineEdit::changeRecord, editor, &pCIOEditor::slotChangeReference );
        }
    }
    return paramWidget;
}

void pIOGuiFactory::searchIORecords( QSharedPointer< pCategory > pCat, QSharedPointer< pIObject > pIO, QString tableName, QAbstractItemView* recView ) {
    if( pCat.isNull() || pIO.isNull() || tableName.isEmpty() || recView == nullptr )
        return;
    qDebug() << __PRETTY_FUNCTION__;
    pSearchForm* pSForm = new pSearchForm( pCat, tableName );
    if( !pSForm || pSForm->exec() != QDialog::Accepted )
        return;
    qDebug() << __PRETTY_FUNCTION__;
}
