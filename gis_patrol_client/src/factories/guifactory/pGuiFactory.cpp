/*
 * @brief Класс-фабрика, управляющий визуальным отображением записей
 * pGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAbstractItemModel>
#include <QWidget>
#include <QtDebug>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pParamListForm.h>
#include <pParamModel.h>
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
}

void PGUIFactory::editGroupOfParams(QAbstractItemModel* paramsModel, qint64 idGroup, QModelIndex wIndex) {
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << idGroup << wIndex;
}

void PGUIFactory::delGroupOfParams(QAbstractItemModel* paramsModel, QModelIndex wIndex) {
    qDebug() << __PRETTY_FUNCTION__ << paramsModel << wIndex;
}
