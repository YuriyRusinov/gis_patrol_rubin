/*
 * @brief Класс-фабрика, управляющий визуальным отображением записей
 * pGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAbstractItemModel>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QWidget>
#include <QtDebug>

#include <defines.h>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pParamListForm.h>
#include <pParamModel.h>
#include <pParamGroup.h>
#include <pParameter.h>
#include <pParamType.h>
#include <paramsgroupform.h>
#include <paramsform.h>
#include "pGuiFactory.h"

PGUIFactory::PGUIFactory(pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent )
    : QObject( parent ), _dbLoader ( dbLoader ), _dbWriter ( dbWriter ) {
}

PGUIFactory::~PGUIFactory () {
}

QWidget* PGUIFactory::GUIView(QWidget* parent, Qt::WindowFlags flags) {
    QWidget* w = new QWidget( parent, flags );
    emit viewWidget( w );
    return w;
}

QWidget* PGUIFactory::GUIViewParams(bool mode, QWidget* parent, Qt::WindowFlags flags) {
    ParamListForm* plf = new ParamListForm( mode, parent, flags );
    QObject::connect( plf, &ParamListForm::addpargroup, this, &PGUIFactory::addGroupOfParams );
    QObject::connect( plf, &ParamListForm::editpargroup, this, &PGUIFactory::editGroupOfParams );
    QObject::connect( plf, &ParamListForm::delpargroup, this, &PGUIFactory::delGroupOfParams );
    QObject::connect( plf, &ParamListForm::addparam, this, &PGUIFactory::addParameter );
    QObject::connect( plf, &ParamListForm::editparam, this, &PGUIFactory::editParameter );
    QObject::connect( plf, &ParamListForm::delparam, this, &PGUIFactory::deleteParameter );
    QObject::connect( plf, &ParamListForm::refreshParams, this, &PGUIFactory::refreshParams );
    QMap< qint64, QSharedPointer< pParamGroup > > pGroups = _dbLoader->loadGroupedParameters();
    QAbstractItemModel* pMod = new ParametersModel( pGroups );
    //this->buildParamModel( pMod, pGroups );
    //QStandardItemModel( pGroups.size(), 1) ;
    plf->setParamsModel( pMod );
    qDebug() << __PRETTY_FUNCTION__ << pGroups.size();
    if (!mode)
        emit viewWidget( plf );
    return plf;
}

void PGUIFactory::addGroupOfParams(QAbstractItemModel* paramsModel, qint64 idParent, QModelIndex pIndex) {
    if( !paramsModel )
        return;
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << idParent << pIndex;
    QString parentName = pIndex.data( Qt::DisplayRole ).toString();
    ParamsGroupForm* pgf = new ParamsGroupForm(-1, QString(), parentName);
    if (pgf->exec() != QDialog::Accepted) {
        delete pgf;
        return;
    }
    QSharedPointer< pParamGroup > parentG = (idParent > 0 ? paramsModel->data(pIndex, Qt::UserRole+1).value< QSharedPointer< pParamGroup >>() : nullptr);
    QSharedPointer< pParamGroup > newGroup ( new pParamGroup( pgf->getId(), pgf->getName(), parentG ) );
    delete pgf;
    qint64 res = _dbWriter->writeParamGroup( newGroup );
    if( res <= 0 ) {
        QWidget* sw = qobject_cast<QWidget *>(this->sender());
        QMessageBox::warning(sw, tr("Write group to database"), tr("Error in attempt to save group"), QMessageBox::Ok);
    }
    int nr = paramsModel->rowCount( pIndex );
    bool isInserted = paramsModel->insertRows( 0, 1, pIndex );
    qDebug() << __PRETTY_FUNCTION__ << isInserted << nr;
    QModelIndex newGroupInd = paramsModel->index( 0, 0, pIndex );
    paramsModel->setData( newGroupInd, QVariant::fromValue<QSharedPointer< pParamGroup >>(newGroup), Qt::UserRole+1);
}

void PGUIFactory::editGroupOfParams(QAbstractItemModel* paramsModel, qint64 idGroup, QModelIndex wIndex) {
    if (!paramsModel || idGroup <= 0 || !wIndex.isValid() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << idGroup << wIndex;
    QString groupName = wIndex.data( Qt::DisplayRole ).toString();
    QString parentName = wIndex.parent().isValid() ? wIndex.parent().data( Qt::DisplayRole ).toString() : QString();
    ParamsGroupForm* pgf = new ParamsGroupForm(idGroup, groupName, parentName);
    if (!pgf || pgf->exec() != QDialog::Accepted) {
        if( pgf )
            delete pgf;
        return;
    }
    QSharedPointer< pParamGroup > parentG = ( wIndex.parent().isValid() ? paramsModel->data(wIndex.parent(), Qt::UserRole+1).value< QSharedPointer< pParamGroup >>() : nullptr);
    QSharedPointer< pParamGroup > edGroup = paramsModel->data(wIndex, Qt::UserRole+1).value< QSharedPointer< pParamGroup >>();
    edGroup->setName( pgf->getName() );
    delete pgf;
    qint64 res = _dbWriter->updateParamGroup( edGroup );
    if( res <= 0 ) {
        QWidget* sw = qobject_cast<QWidget *>(this->sender());
        QMessageBox::warning(sw, tr("Update group in database"), tr("Error in attempt to save group"), QMessageBox::Ok);
    }
    paramsModel->setData( wIndex, QVariant::fromValue<QSharedPointer< pParamGroup >>(edGroup), Qt::UserRole+1);
}

void PGUIFactory::delGroupOfParams(QAbstractItemModel* paramsModel, QModelIndex wIndex) {
    if (!paramsModel || !wIndex.isValid() )
        return;
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << wIndex;
    int nr = paramsModel->rowCount( wIndex );
    QWidget* sw = qobject_cast<QWidget *>(this->sender());
    if (nr > 0) {
        QMessageBox::warning( sw, tr("Delete group"), tr("Cannot delete not empty group"), QMessageBox::Ok );
        return;
    }
    QMessageBox::StandardButton res = QMessageBox::question( sw, tr("Delete group"), tr("Do you really want to delete group ?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No );
    if (res != QMessageBox::Yes)
        return;

    qint64 idRes = _dbWriter->deleteParamGroup( wIndex.data(Qt::UserRole).toInt() );
    if (idRes < 0) {
        QMessageBox::warning( sw, tr("Delete group"), tr("DB Error in delete group"), QMessageBox::Ok );
        return;
    }
    QModelIndex pIndex = wIndex.parent();
    paramsModel->removeRows(wIndex.row(), 1, pIndex);
}

void PGUIFactory::addParameter( QAbstractItemModel* paramsModel, qint64 idParentGroup, QModelIndex pIndex ) {
    QMap< qint64, QSharedPointer<pParamType> > pTypes = _dbLoader->loadAvailParamTypes();
    ParamsForm* parForm = new ParamsForm( -1, pTypes );
    if (!parForm || parForm->exec() != QDialog::Accepted) {
        if (parForm)
            delete parForm;
        return;
    }
    QSharedPointer< pParamType > pType = parForm->getParamType();
    QSharedPointer< pParamGroup > pGroup = paramsModel->data( pIndex, Qt::UserRole+1 ).value< QSharedPointer< pParamGroup > >();
    if( pGroup.isNull() )
        pGroup = _dbLoader->loadParamGroup( idParentGroup );
    QString paramName = parForm->getName();
    QString paramCode = parForm->getCode();
    QString paramTitle = parForm->getTitle();
    QString tableName = QString();
    QString columnName = QString();
    if (pType->getId() == 2 || pType->getId() == 27) {
        tableName = parForm->getTableName();
        columnName = parForm->getColumnName();
    }
    QSharedPointer< pParameter > pParam( new pParameter(-1, pType, pGroup, paramCode, paramName, paramTitle, tableName, columnName) );
    qint64 idParam = _dbWriter->insertParam( pParam );
    if (idParam <= 0) {
        QWidget* sw = qobject_cast<QWidget *>(this->sender());
        QMessageBox::warning( sw, tr("New parameter"), tr("Cannot insert parameter, DB error"), QMessageBox::Ok );
        return;
    }
    int nr = paramsModel->rowCount( pIndex );
    bool isInserted = paramsModel->insertRows( nr, 1, pIndex );
    qDebug() << __PRETTY_FUNCTION__ << isInserted;
    QModelIndex wIndex = paramsModel->index( nr, 0, pIndex );
    paramsModel->setData(wIndex, QVariant::fromValue<QSharedPointer< pParameter >>( pParam ), Qt::UserRole+1);
}
void PGUIFactory::editParameter( QAbstractItemModel* paramsModel, qint64 idParameter, QModelIndex wIndex ) {
    if (!paramsModel || !wIndex.isValid() || idParameter <= 0)
        return;
    QSharedPointer< pParameter > pParam = paramsModel->data(wIndex, Qt::UserRole+1).value< QSharedPointer< pParameter >> ();
    if (!pParam)
        return;
    QMap< qint64, QSharedPointer<pParamType> > pTypes = _dbLoader->loadAvailParamTypes();
    ParamsForm* parForm = new ParamsForm( idParameter, pTypes );
    if (!parForm )
        return;

    QSharedPointer< pParamType> pType = pParam->getParamType();
    parForm->setParamType( pType->getId() );
    parForm->setName( pParam->getName() );
    parForm->setCode( pParam->getCode() );
    parForm->setTitle( pParam->getTitle() );
    parForm->setTableName( pParam->getTableName() );
    parForm->setColumnName( pParam->getColumnName() );
    if (parForm->exec() != QDialog::Accepted) {
        delete parForm;
        return;
    }
    QString paramName = parForm->getName();
    QString paramCode = parForm->getCode();
    QString paramTitle = parForm->getTitle();
    QString tableName = QString();
    QString columnName = QString();
    if (pType->getId() == 2 || pType->getId() == 27) {
        tableName = parForm->getTableName();
        columnName = parForm->getColumnName();
    }
    pParam->setName( paramName );
    pParam->setCode( paramCode );
    pParam->setTitle( paramTitle );
    pParam->setTableName( tableName );
    pParam->setColumnName( columnName );
    delete parForm;
    qint64 idParam = _dbWriter->updateParam( pParam );
    if (idParam < 0 || idParam != idParameter) {
        QWidget* sw = qobject_cast<QWidget *>(this->sender());
        QMessageBox::warning( sw, tr("Edit parameter"), tr("Cannot update parameter, DB error"), QMessageBox::Ok );
        return;
    }
    paramsModel->setData( wIndex, QVariant::fromValue<QSharedPointer< pParameter >>( pParam ), Qt::UserRole+1);
}

void PGUIFactory::deleteParameter( QAbstractItemModel* paramsModel, QModelIndex wIndex ) {
    if( !paramsModel || !wIndex.isValid() )
        return;
    int nr = paramsModel->rowCount( wIndex );
    QWidget* sw = qobject_cast<QWidget *>(this->sender());
    if (nr > 0) {
        QMessageBox::warning( sw, tr("Delete parameter"), tr("Cannot delete parameter"), QMessageBox::Ok );
        return;
    }
    QMessageBox::StandardButton res = QMessageBox::question( sw, tr("Delete parameter"), tr("Do you really want to delete parameter ?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No );
    if (res != QMessageBox::Yes)
        return;
    qint64 idRes = _dbWriter->deleteParam( wIndex.data(Qt::UserRole).toInt() );
    if (idRes < 0) {
        QMessageBox::warning( sw, tr("Delete parameter"), tr("DB Error in delete parameter"), QMessageBox::Ok );
        return;
    }
    QModelIndex pIndex = wIndex.parent();
    paramsModel->removeRows(wIndex.row(), 1, pIndex);
}

void PGUIFactory::refreshParams() {
    ParamListForm* plf = qobject_cast< ParamListForm *>(this->sender());
    if (!plf)
        return;
    QMap< qint64, QSharedPointer< pParamGroup > > pGroups = _dbLoader->loadGroupedParameters();
    ParametersModel* pMod = new ParametersModel( pGroups );
    plf->setParamsModel( pMod );
}

void PGUIFactory::buildParamModel( QAbstractItemModel* pMod, const QMap< qint64, QSharedPointer< pParamGroup >>& pGroups, QModelIndex parent) const {
    int i=0;
    if (pMod->rowCount(parent) > 0) {
        int nr = pMod->rowCount();
        pMod->removeRows(0, nr, parent);
    }
    if (pMod->columnCount( parent ) == 0)
        pMod->insertColumns(0, 1, parent );
    pMod->insertRows( 0, pGroups.size(), parent );
    for (QMap< qint64, QSharedPointer< pParamGroup > >::const_iterator pgr = pGroups.constBegin();
            pgr != pGroups.constEnd();
            pgr++) {
        QModelIndex wIndex = pMod->index(i, 0, parent);
        pMod->setData( wIndex, pgr.key(), Qt::UserRole);
        //pMod->setData( wIndex, QVariant::fromValue< QSharedPointer< pParamGroup > > (pgr.value()), Qt::UserRole+1);
        pMod->setData( wIndex, 0 /*pgr.value()->getEntity()*/, Qt::UserRole+USER_ENTITY);
        pMod->setData( wIndex, pgr.value()->getName(), Qt::DisplayRole );
        int nchildren = pgr.value()->getChildGroups().size();
        if ( nchildren > 0) {
            buildParamModel( pMod, pgr.value()->getChildGroups(), wIndex );
        }

        for( QMap<qint64, QSharedPointer< pParameter >>::const_iterator pa = pgr.value()->getParameters().constBegin();
                pa != pgr.value()->getParameters().constEnd();
                pa++ ) {
            int nr = pMod->rowCount( wIndex );
            pMod->insertRows(nr, 1, wIndex );
            if (pMod->columnCount( wIndex ) == 0)
                pMod->insertColumns(0, 1, wIndex );
            QModelIndex wpIndex = pMod->index( nr, 0, wIndex );
            pMod->setData( wpIndex, pa.key(), Qt::UserRole );
            //pMod->setData( wpIndex, QVariant::fromValue< QSharedPointer< pParameter >>(pa.value()), Qt::UserRole+1 );
            pMod->setData( wpIndex, 1/*pa.value()->getEntity()*/, Qt::UserRole+USER_ENTITY);
            pMod->setData( wpIndex, pa.value()->getName(), Qt::DisplayRole );
        }
        i++;
    }
}
