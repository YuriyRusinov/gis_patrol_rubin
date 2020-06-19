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
#include <QWidget>
#include <QtDebug>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pParamListForm.h>
#include <pParamModel.h>
#include <pParamGroup.h>
#include <pParameter.h>
#include <paramsgroupform.h>
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
    QMap< qint64, QSharedPointer< pParamGroup > > pGroups = _dbLoader->loadGroupedParameters();
    ParametersModel* pMod = new ParametersModel( pGroups );
    plf->setParamsModel( pMod );
    qDebug() << __PRETTY_FUNCTION__ << pGroups.size();
    if (!mode)
        emit viewWidget( plf );
    return plf;
}

void PGUIFactory::addGroupOfParams(QAbstractItemModel* paramsModel, qint64 idParent, QModelIndex pIndex) {
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << idParent << pIndex;
    QString parentName = pIndex.data(Qt::DisplayRole).toString();
    ParamsGroupForm* pgf = new ParamsGroupForm(-1, QString(), parentName);
    if (pgf->exec() == QDialog::Accepted) {
        qDebug() << __PRETTY_FUNCTION__ << "New group";
    }
    QSharedPointer< pParamGroup > parentG = (idParent > 0 ? paramsModel->data(pIndex, Qt::UserRole+1).value< QSharedPointer< pParamGroup >>() : nullptr);
    QSharedPointer< pParamGroup > newGroup ( new pParamGroup( pgf->getId(), pgf->getName(), parentG ) );
    qint64 res = _dbWriter->writeParamGroup( newGroup );
    if( res <= 0 ) {
        QWidget* sw = qobject_cast<QWidget *>(this->sender());
        QMessageBox::warning(sw, tr("Write group to database"), tr("Error in attempt to save group"), QMessageBox::Ok);
    }
    int nr = paramsModel->rowCount( pIndex );
    bool isInserted = paramsModel->insertRows( nr, 1, pIndex );
    qDebug() << __PRETTY_FUNCTION__ << isInserted;
    QModelIndex newGroupInd = paramsModel->index( nr, 0, pIndex );
    paramsModel->setData( newGroupInd, QVariant::fromValue<QSharedPointer< pParamGroup >>(newGroup), Qt::UserRole+1);
}

void PGUIFactory::editGroupOfParams(QAbstractItemModel* paramsModel, qint64 idGroup, QModelIndex wIndex) {
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << idGroup << wIndex;
}

void PGUIFactory::delGroupOfParams(QAbstractItemModel* paramsModel, QModelIndex wIndex) {
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << wIndex;
}
