/*
 * @brief Класс-виджет, содержащий список параметров и элементы управления им
 * pParamListForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAbstractItemModel>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QGridLayout>
#include <QButtonGroup>
#include <QToolBar>
#include <QTreeView>
#include <QAction>
#include <QMessageBox>
#include <QtDebug>
#include <defines.h>
#include "pParamListForm.h"

ParamListForm::ParamListForm(bool mode, QWidget* parent, Qt::WindowFlags flags)
    : QDialog( parent, flags),
    _tbParamActions( new QToolBar ),
    _tvParams( new QTreeView ),
    _bgParams( new QButtonGroup ) {

    QGridLayout* gLay = new QGridLayout( this );
    gLay->addWidget( _tbParamActions, 0, 0, 1, 1 );
    gLay->addWidget( _tvParams, 1, 0, 1, 1);
//    gLay->addWidget( _bgParams, 2, 0, 1, 1);
    init(mode);
}

ParamListForm::~ParamListForm() {
    delete _bgParams;
    delete _tvParams;
    delete _tbParamActions;
}

QAbstractItemModel* ParamListForm::getParamsModel() const {
    return _tvParams->model();
}

void ParamListForm::setParamsModel( QAbstractItemModel* paramsModel ) {
    QAbstractItemModel* oldModel = _tvParams->model();
    _tvParams->setModel( paramsModel );
    if (oldModel && oldModel != paramsModel)
        delete oldModel;
}

void ParamListForm::addParamGroup() {
    qDebug() << __PRETTY_FUNCTION__;
    QModelIndex parentIndex = getGroupIndex();
    qint64 idParent = parentIndex.isValid() ? parentIndex.data(Qt::UserRole).toInt() : -1;
    qDebug() << __PRETTY_FUNCTION__ << parentIndex << idParent << parentIndex.data(Qt::UserRole+USER_ENTITY).toInt();
    emit addpargroup( _tvParams->model(), idParent, parentIndex );
}

void ParamListForm::editParamGroup() {
    qDebug() << __PRETTY_FUNCTION__;
    QModelIndex wIndex = getGroupIndex();
    if (!wIndex.isValid()) {
        QMessageBox::warning( this, tr("Edit group"), tr("Please select group for edit"), QMessageBox::Ok );
        return;
    }
    qint64 idGroup = wIndex.data( Qt::UserRole ).toInt();
    emit editpargroup( _tvParams->model(), idGroup, wIndex );
}

void ParamListForm::delParamGroup() {
    qDebug() << __PRETTY_FUNCTION__;
    QModelIndex wIndex = getGroupIndex();
    if (!wIndex.isValid()) {
        QMessageBox::warning( this, tr("Delete group"), tr("Please select group for remove"), QMessageBox::Ok );
        return;
    }
    int numChildren = _tvParams->model()->rowCount( wIndex );
    if (numChildren > 0) {
        QMessageBox::warning( this, tr("Delete group"), tr("Group is not empty, removing is impossible"), QMessageBox::Ok );
        return;
    }
    emit delpargroup( _tvParams->model(), wIndex );
}

void ParamListForm::addParameter() {
    qDebug() << __PRETTY_FUNCTION__;
    QModelIndex wIndex = getGroupIndex();
    if (!wIndex.isValid()) {
        QMessageBox::warning( this, tr("Add parameter"), tr("Please select parent group for parameter"), QMessageBox::Ok );
        return;
    }
    qint64 idGroup = wIndex.data( Qt::UserRole ).toLongLong();
    emit addparam( _tvParams->model(), idGroup, wIndex );
}

void ParamListForm::editParameter() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::delParameter() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::refreshAll() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::init(bool mode) {
    _tvParams->setSelectionMode( mode ? QAbstractItemView::ExtendedSelection : QAbstractItemView::SingleSelection);

    _tbParamActions->setVisible ( !mode );
//    _bgParams->setVisible( mode );

    QAction* actAddParamGroup = _tbParamActions->addAction( QIcon(":/patrol/add_parameter.svg"), tr("Add group of parameters"));
    actAddParamGroup->setToolTip( tr("Add new group of parameters") );
    QObject::connect( actAddParamGroup, &QAction::triggered, this, &ParamListForm::addParamGroup );

    QAction* actEditParamGroup = _tbParamActions->addAction( QIcon(":/patrol/edit_parameter.svg"), tr("Edit group of parameters"));
    actEditParamGroup->setToolTip( tr("Edit group of parameters") );
    QObject::connect( actEditParamGroup, &QAction::triggered, this, &ParamListForm::editParamGroup );

    QAction* actDelParamGroup = _tbParamActions->addAction( QIcon(":/patrol/del_parameter.svg"), tr("Delete group of parameters"));
    actDelParamGroup->setToolTip( tr("Delete group of parameters") );
    QObject::connect( actDelParamGroup, &QAction::triggered, this, &ParamListForm::delParamGroup );

    _tbParamActions->addSeparator();

    QAction* actAddParameter = _tbParamActions->addAction( QIcon(":/patrol/add_parameter.svg"), tr("Add parameter") );
    actAddParameter->setToolTip( tr("Add new parameter") );
    QObject::connect( actAddParameter, &QAction::triggered, this, &ParamListForm::addParameter );

    QAction* actEditParameter = _tbParamActions->addAction( QIcon(":/patrol/edit_parameter.svg"), tr("Edit parameter") );
    actEditParameter->setToolTip( tr("Edit parameter") );
    QObject::connect( actEditParameter, &QAction::triggered, this, &ParamListForm::editParameter );

    QAction* actDelParameter = _tbParamActions->addAction( QIcon(":/patrol/del_parameter.svg"), tr("Delete parameter") );
    actDelParameter->setToolTip( tr("Delete parameter") );
    QObject::connect( actDelParameter, &QAction::triggered, this, &ParamListForm::delParameter );

    _tbParamActions->addSeparator();
    QAction* actRefresh = _tbParamActions->addAction( QIcon(":/patrol/refresh_parameters.svg"), tr( "Refresh") );
    actRefresh->setToolTip( tr("Refresh") );
    QObject::connect( actRefresh, &QAction::triggered, this, &ParamListForm::refreshAll );
}

QModelIndex ParamListForm::getGroupIndex() const {
    QItemSelectionModel* selMod = _tvParams->selectionModel();
    QItemSelection selInd = selMod->selection();
    QModelIndex parentIndex = selInd.empty() ? QModelIndex() : selInd.indexes().at(0);
    qint64 idParent = parentIndex.isValid() ? parentIndex.data(Qt::UserRole).toInt() : -1;
    if( selInd.empty() || idParent < 0 )
        return QModelIndex();
    QAbstractItemModel* sourceMod = _tvParams->model();

    for (; sourceMod->data(parentIndex, Qt::UserRole+USER_ENTITY).toInt() != 0 && parentIndex.isValid(); parentIndex = parentIndex.parent() )
        ;
    return parentIndex;
}

QModelIndex ParamListForm::getParamIndex() const {
    QItemSelectionModel* selMod = _tvParams->selectionModel();
    QItemSelection selInd = selMod->selection();
    if( selInd.empty() )
        return QModelIndex();
    QModelIndex paramIndex = selInd.indexes().at(0);
    QAbstractItemModel* sourceMod = _tvParams->model();
    if (sourceMod->data( paramIndex, Qt::UserRole+USER_ENTITY ).toInt() == 0) // group
        return QModelIndex();

    return paramIndex;
}
