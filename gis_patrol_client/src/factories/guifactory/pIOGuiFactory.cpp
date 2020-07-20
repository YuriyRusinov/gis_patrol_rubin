/*
 * @brief Класс-фабрика для информационных объектов и записей
 * pIOGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QGridLayout>
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

    QMap< qint64, QSharedPointer< pRecordCopy > > ioRecords = _dbLoader->loadRecords( pIO );
    QTreeView* tvRecs = new QTreeView( wEditor );
    QAbstractItemModel* recModel = new pRecordDataModel( pCat->getTableCat(), ioRecords );
    tvRecs->setModel( recModel );
    QWidget* parWidget = viewRecParams( pCat->getTableCat(), pRec, wEditor );
    if( parWidget )
        wEditor->appendTabWidget( parWidget, tr("System properties") );
    wEditor->appendTabWidget( tvRecs, tr("Records") );
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
        //
        // Тут важно, что параметр будет скопирован, так как есть необходимость на уровне редактирования
        // вносить возможные изменения в слоте редактора
        //
        QSharedPointer< pParamValue > pval ( new pParamValue (*pRec->paramValue( pca.value()->getId() )));
        pAbstractParamWidget* pw = _paramFactory->createParamWidget( pval, paramWidget );
        if( pw != nullptr ) {
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

void pIOGuiFactory::loadParamRef( QSharedPointer< pParamValue > pValue, QString tableName, QString columnName ) {
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
    qDebug() << __PRETTY_FUNCTION__ << pCat->getId() << pCat->getTableCat()->getId();
    QAbstractItemModel* recModel = new pRecordDataModel( pCat->getTableCat(), ioRecords );
    pRecDialog* pRecF = new pRecDialog;
    pRecF->setRecModel( recModel );
    if( pRecF == nullptr || pRecF->exec() != QDialog::Accepted ) {
        if( pRecF )
            delete pRecF;
        return;
    }
    qint64 idRec = pRecF->getRecId();
    qDebug() << __PRETTY_FUNCTION__ << idRec;
    delete pRecF;
}
