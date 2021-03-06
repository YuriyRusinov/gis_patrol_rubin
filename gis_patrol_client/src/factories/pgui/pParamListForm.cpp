/*
 * @brief Класс-виджет, содержащий список параметров и элементы управления им
 * pParamListForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAbstractItemModel>
#include <QAction>
#include <QDialogButtonBox>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QGridLayout>
#include <QButtonGroup>
#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QtDebug>

#include <defines.h>
#include <pParameter.h>
#include "pItemDelegate.h"
#include "pParamListForm.h"

ParamListForm::ParamListForm(bool mode, QWidget* parent, Qt::WindowFlags flags)
    : QDialog( parent, flags),
    _tbParamActions( new QToolBar ),
    _tvParams( new QTreeView ),
    _bgParams( new QButtonGroup ),
    _dbbParams( new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel) ) {

    QAbstractItemDelegate* pDeleg = new pItemDelegate;
    _tvParams->setItemDelegate( pDeleg );
    QGridLayout* gLay = new QGridLayout( this );
    gLay->addWidget( _tbParamActions, 0, 0, 1, 1 );
    gLay->addWidget( _tvParams, 1, 0, 1, 1);
    gLay->addWidget( _dbbParams, 2, 0, 1, 1);
//    gLay->addWidget( _bgParams, 2, 0, 1, 1);
    init(mode);
}

ParamListForm::~ParamListForm() {
    delete _dbbParams;
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
    QModelIndex wIndex = getParamIndex();
    if (!wIndex.isValid()) {
        QMessageBox::warning( this, tr("Edit parameter"), tr("Please select parameter for edit"), QMessageBox::Ok );
        return;
    }
    qint64 idParam = wIndex.data( Qt::UserRole ).toLongLong();
    emit editparam( _tvParams->model(), idParam, wIndex );
}

void ParamListForm::delParameter() {
    qDebug() << __PRETTY_FUNCTION__;
    QModelIndex wIndex = getParamIndex();
    if (!wIndex.isValid()) {
        QMessageBox::warning( this, tr("Delete parameter"), tr("Please select parameter for delete"), QMessageBox::Ok );
        return;
    }
    emit delparam( _tvParams->model(), wIndex );
}

void ParamListForm::refreshAll() {
    qDebug() << __PRETTY_FUNCTION__;
    emit refreshParams();
}

void ParamListForm::init(bool mode) {
    _tvParams->setSelectionMode( mode ? QAbstractItemView::ExtendedSelection : QAbstractItemView::SingleSelection );

    _tbParamActions->setVisible ( !mode );
    _dbbParams->setVisible ( mode );
    QObject::connect( _dbbParams, &QDialogButtonBox::accepted, this, &QDialog::accept );
    QObject::connect( _dbbParams, &QDialogButtonBox::rejected, this, &QDialog::reject );
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

QModelIndexList ParamListForm::getParamsIndexList() const {
    QItemSelectionModel* selMod = _tvParams->selectionModel();
    QItemSelection selInd = selMod->selection();
    if( selInd.empty() )
        return selInd.indexes();
    QAbstractItemModel* sourceMod = _tvParams->model();

    QModelIndexList wIndexes = selMod->selectedRows( 0 );
    QModelIndexList res;
    for (int i=0; i<wIndexes.size(); i++) {
        QModelIndex wIndex = wIndexes.at( i );//selInd.indexes().at(i);
        if( sourceMod->data( wIndex, Qt::UserRole+USER_ENTITY ).toInt() == 1 )
            res.append( wIndex );
    }
    return res;
}

QMap< qint64, QSharedPointer< pParameter > > ParamListForm::getParameters() const {
    QItemSelectionModel* selMod = _tvParams->selectionModel();
    QItemSelection selInd = selMod->selection();
    QAbstractItemModel* sourceMod = selMod->model();
    qDebug() << __PRETTY_FUNCTION__ << "Number of rows is " << sourceMod->rowCount();
    Q_UNUSED( sourceMod );
    if( selInd.empty() )
        return QMap< qint64, QSharedPointer< pParameter > >();

    QMap< qint64, QSharedPointer< pParameter > > selParams;
    QModelIndexList selParamIndexes = getParamsIndexList();
    qDebug() << __PRETTY_FUNCTION__ << selInd.indexes().size();
    for (int i=0; i< selParamIndexes.size(); i++) {
        QModelIndex wIndex = selParamIndexes[i];;
        qDebug() << __PRETTY_FUNCTION__ << wIndex;
        if (wIndex.data( Qt::UserRole+USER_ENTITY ).toInt() != 1) {
            continue;
        }
        qDebug() << __PRETTY_FUNCTION__ << "Parameter";
        qint64 pId = wIndex.data( Qt::UserRole ).toLongLong();
        QSharedPointer< pParameter > pPar = wIndex.data( Qt::UserRole+1 ).value< QSharedPointer< pParameter > > ();
        if ( !selParams.contains( pId ) )
            selParams.insert( pId, pPar );
    }

    return selParams;
}
