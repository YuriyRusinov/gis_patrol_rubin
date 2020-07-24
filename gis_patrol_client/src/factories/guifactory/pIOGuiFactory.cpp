/*
 * @brief Класс-фабрика для информационных объектов и записей
 * pIOGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

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

#include "pParamGuiFactory.h"
#include "pIOGuiFactory.h"

QWidget* pIOGuiFactory::GUIView( QWidget* parent, Qt::WindowFlags flags ) {
    QSharedPointer< pIObject > pIO = _dbLoader->loadIO( IO_IO_ID );
    QSharedPointer< pRecordCopy > pRec = _dbLoader->loadCopy( IO_IO_ID, pIO );
    if (pIO.isNull() || pRec.isNull() )
        return nullptr;

    QSharedPointer< pCategory > pCat = pIO->getCategory();

    pCIOEditor* wEditor = new pCIOEditor( pCat, pRec, pIO, false, parent, flags );
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

    QMap< qint64, QSharedPointer< pRecordCopy > > ioRecords = _dbLoader->loadRecords( pIO );
    pRecWidget* recWidget = createRecordsWidget( pIO, wEditor );// new pRecWidget( wEditor );
    QWidget* parWidget = viewRecParams( pCat->getTableCat(), pRec, wEditor );
    if( parWidget )
        wEditor->appendTabWidget( parWidget, tr("System properties") );
    wEditor->appendTabWidget( recWidget, tr("Records") );
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

QWidget* pIOGuiFactory::viewRecParams( QSharedPointer< pCategory > pCategory, QSharedPointer< pRecordCopy > pRec, pCIOEditor* editor, QWidget* parent, Qt::WindowFlags flags ) const {
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
        if( pRec->paramValue( pca.value()->getId() ).isNull() ) {
            //
            // Something incorrect, debug output
            //
            qDebug() << __PRETTY_FUNCTION__ << QString("Null parameter %1 in record, category is %2").arg( pca.value()->getCode() ).arg ( pCategory->getId() );
            continue;
        }
        else
            pval = QSharedPointer< pParamValue >( pRec->paramValue( pca.value()->getId() ));
        pAbstractParamWidget* pw = _paramFactory->createParamWidget( pval, paramWidget );
        bool readOnlyVal = pca.value()->isReadOnly() && pRec->getId() > 0;
//        if( pca.value()->getId() == 16)
        qDebug() << __PRETTY_FUNCTION__ << pca.value()->getId() << pval.isNull() << (pw == nullptr ) << pca.value()->getParamType()->getId();
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

void pIOGuiFactory::saveRecToDb( QSharedPointer< pRecordCopy > pr, QSharedPointer< pIObject > pIO ) {
    int res = 0;
    if( pr->getId() < 0 )
        res = _dbWriter->insertRecord( pr, pIO );
    else
        res = _dbWriter->updateRecord( pr, pIO );

    if( res < 0 ) {
        QWidget* w = qobject_cast<QWidget*>( this->sender() );
        QMessageBox::warning( w, tr("Save record"), tr("Save record %1, DB error code %2").arg( pr->getId() ).arg( res ), QMessageBox::Ok );
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
    qDebug() << __PRETTY_FUNCTION__ << pRec->getIO()->getId() << pRec->getId();
    QSharedPointer< pCategory > pCat = pRec->getIO()->getCategory();
    pCIOEditor* wEditor = createRecEditor( pCat, pRefIO, pRec );
    emit viewWidget( wEditor );
}

void pIOGuiFactory::openRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex ) {
    qDebug() << __PRETTY_FUNCTION__ << pRec.isNull() << pRefIO.isNull() << (recModel == nullptr) << recIndex.isValid();
    if( pRec.isNull() || pRefIO.isNull() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << pRec->getIO()->getId() << pRec->getId();
    QSharedPointer< pCategory > pCat = pRec->getIO()->getCategory();
    pCIOEditor* wEditor = createRecEditor( pCat, pRefIO, pRec );
    emit viewWidget( wEditor );
}

void pIOGuiFactory::removeRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex ) {
    qDebug() << __PRETTY_FUNCTION__ << pRec.isNull() << pRefIO.isNull() << (recModel == nullptr) << recIndex.isValid();
}

pCIOEditor* pIOGuiFactory::createRecEditor( QSharedPointer< pCategory > pRecCategory, QSharedPointer< pIObject > pRefIO, QSharedPointer< pRecordCopy > pRec, QWidget* parent, Qt::WindowFlags flags ) const {
    if( pRecCategory.isNull() || pRefIO.isNull() || pRec.isNull() )
        return nullptr;

    pCIOEditor* wEditor = new pCIOEditor( pRecCategory, pRec, pRefIO, false, parent, flags );
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
    QWidget* parWidget = viewRecParams( pRecCategory->getTableCat(), pRec, wEditor );
    if( parWidget )
        wEditor->appendTabWidget( parWidget, tr("System properties") );
    QSharedPointer< pIObject > pRecIO ( nullptr );
    if( pRefIO->getId() == IO_IO_ID && pRec->getIO()->getId() == IO_IO_ID ) {
        pRecIO = _dbLoader->loadIO( pRec->getId() );
        QMap< qint64, QSharedPointer< pRecordCopy > > ioRecords = _dbLoader->loadRecords( pRecIO );
        pRecWidget* recWidget = createRecordsWidget( pRecIO, wEditor );
        //QAbstractItemModel* recModel = new pRecordDataModel( pRefIO->getCategory()->getTableCat(), ioRecords );
        //recWidget->setSourceModel( recModel );
        wEditor->appendTabWidget( recWidget, tr("Records") );
    }
    return wEditor;
}
