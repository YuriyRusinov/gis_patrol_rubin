/*
 * @brief Виджет редактирования записей
 * pCIOEditor.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAction>
#include <QKeySequence>
#include <QGridLayout>
#include <QModelIndex>
#include <QTabWidget>
#include <QToolBar>
#include <QtDebug>

#include <pCategory.h>
#include <pRecord.h>
#include <pRecordC.h>
#include <pIObject.h>
#include <pCatParameter.h>
#include <pParamValue.h>
#include <pParamType.h>
#include "pAbstractParamWidget.h"
#include "pCIOEditor.h"

pCIOEditor::pCIOEditor( QSharedPointer< pCategory > pCategory,
                        QSharedPointer< pRecordCopy > pRec,
                        QSharedPointer< pIObject > pIO,
                        bool isIO,
                        QWidget* parent,
                        Qt::WindowFlags flags
                    )
    : QWidget( parent, flags ),
    _pCategory( pCategory ),
    _pRecord( pRec ),
    _pIO( pIO ),
    _isIO( isIO ),
    _tbIOActions( new QToolBar ),
    _tabW( new QTabWidget ),
    _isChanged( pRec->getId() < 0 ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _tbIOActions, 0, 0, 1, 1 );
    grLay->addWidget( _tabW, 1, 0, 1, 1 );

    initActions();
}

pCIOEditor::~pCIOEditor() {
    delete _tbIOActions;
    delete _tabW;
}

QSharedPointer< const pCategory > pCIOEditor::getCategory() const {
    return _pCategory;
}

void pCIOEditor::setCategory( QSharedPointer< pCategory > pc ) {
    _pCategory = pc;
}

QSharedPointer< const pRecordCopy > pCIOEditor::getRecord() const {
    return _pRecord;
}

void pCIOEditor::setRecord ( QSharedPointer< pRecordCopy > pr ) {
    _pRecord = pr;
}

QSharedPointer< const pIObject > pCIOEditor::getObject() const {
    return _pIO;
}

void pCIOEditor::setObject( QSharedPointer< pIObject > pIO ) {
    _pIO = pIO;
}

void pCIOEditor::initActions() {
    QAction* actSaveRec = _tbIOActions->addAction( QIcon(":/patrol/save_db.png"), tr("Save record to DB") );
    actSaveRec->setToolTip( tr("Save record to database") );
    QKeySequence ksSave( Qt::CTRL | Qt::Key_S );
    actSaveRec->setShortcut( ksSave );
    QObject::connect( actSaveRec, &QAction::triggered, this, &pCIOEditor::slotSaveRecord );

    _tbIOActions->addSeparator();
}

void pCIOEditor::createNewRecord( QAbstractItemModel* recModel ) {
    if( !recModel )
        return;
    QSharedPointer< pRecordCopy > rec( new pRecordCopy( -1, QString(), _pIO ) );
    qDebug() << __PRETTY_FUNCTION__ << _pIO->getId();
    emit createRecord( rec, _pIO, recModel );
}

void pCIOEditor::editSelRecord( QAbstractItemModel* recMod, const QModelIndex& recIndex ) {
    if( !recMod || !recIndex.isValid() )
        return;
    QSharedPointer< const pRecordCopy > recC = recMod->data( recIndex, Qt::UserRole+1 ).value< QSharedPointer< const pRecordCopy > >();
    QSharedPointer< pRecordCopy > rec( qSharedPointerConstCast< pRecordCopy >(recC) );
    qDebug() << __PRETTY_FUNCTION__ << (rec.isNull() ? -1 : rec->getId() ) << _pIO->getId();
    emit openRecord( rec, _pIO, recMod, recIndex );
}

void pCIOEditor::delSelRecord( QAbstractItemModel* recMod, const QModelIndex& recIndex ) {
    if( !recMod || !recIndex.isValid() )
        return;
    QSharedPointer< const pRecordCopy > recC = recMod->data( recIndex, Qt::UserRole+1 ).value< QSharedPointer< const pRecordCopy > >();
    QSharedPointer< pRecordCopy > rec( qSharedPointerConstCast< pRecordCopy >(recC) );
    emit delRecord( rec, _pIO, recMod, recIndex );
    qDebug() << __PRETTY_FUNCTION__ << (rec.isNull() ? -1 : rec->getId() );
}

void pCIOEditor::appendTabWidget( QWidget* w, QString title ) {
    _tabW->addTab( w, title );
}

void pCIOEditor::slotParamRecChanged( QSharedPointer< pParamValue > pValue ) {
    if( pValue.isNull() )
        return;
    qint64 pId = pValue->getCatParam()->getId();
    QSharedPointer< pParamValue > pVal = _pRecord->paramValue( pId );
    if( pVal.isNull() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << QString("Old value is %1").arg(pVal->value().toString()) << pValue->value().toString();
    pVal->setValue( pValue->value() );
    _pRecord->paramValue( pId ) = pVal;
    _isChanged = true;
}

void pCIOEditor::slotSaveRecord() {
    if( _isIO ) {
        qDebug() << __PRETTY_FUNCTION__ << _pRecord->getId() << _pIO->getId();
        emit saveRecordIO( _pRecord, _pIO );
        return;
    }
    emit saveRecord( _pRecord, _pIO );
}

void pCIOEditor::slotChangeReference( QSharedPointer< pParamValue > pValue, QLineEdit* lE ) {
    qDebug() << __PRETTY_FUNCTION__;
    if( pValue.isNull() || pValue->getCatParam().isNull() )
        return;
    QString tableName = pValue->getCatParam()->getParamType()->getId() == pParamType::atParent ? _pIO->getTableName() : pValue->getCatParam()->getTableName();
    QString columnName = pValue->getCatParam()->getColumnName();
    qDebug() << __PRETTY_FUNCTION__ << tableName << columnName << _pIO->getTableName();
    emit loadReferenceRecords( _pRecord, pValue, tableName, columnName, lE );
}
