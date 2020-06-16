/*
 * @brief Класс-виджет, содержащий список параметров и элементы управления им
 * pParamListForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAbstractItemModel>
#include <QGridLayout>
#include <QButtonGroup>
#include <QToolBar>
#include <QTreeView>
#include <QAction>
#include <QtDebug>
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
}

void ParamListForm::editParamGroup() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::delParamGroup() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::addParameter() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::editParameter() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::delParameter() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::refresh() {
    qDebug() << __PRETTY_FUNCTION__;
}

void ParamListForm::init(bool mode) {
    _tvParams->setSelectionMode( QAbstractItemView::ExtendedSelection );

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
}
