/*
 * @brief Данный класс унаследован от QWidget и предназначен для визуализации и редактирования категории
 * pCatEditor.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAbstractItemModel>
#include <QAction>
#include <QComboBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QTabWidget>
#include <QToolBar>
#include <QTreeView>
#include <QtDebug>

#include <pCategory.h>
#include <pCategoryType.h>

#include "pCatEditor.h"

pCatEditor::pCatEditor( QSharedPointer< pCategory > pCat, const QMap< qint64, QSharedPointer< pCategoryType > >& pAvailCatTypes, QWidget* parent, Qt::WindowFlags flags )
    : QWidget( parent, flags ),
    _pCategory( pCat ),
    _availCatTypes( pAvailCatTypes ),
    _tbCatActions( new QToolBar ),
    _tabCatWidget( new QTabWidget ),
    _catParamWidget( new QWidget ),
    _lCatName( new QLabel( tr("Name:") ) ),
    _lECatName( new QLineEdit ),
    _lCatCode( new QLabel( tr("Code:") ) ),
    _lECatCode( new QLineEdit ),
    _lCatDesc( new QLabel( tr("Description:") ) ),
    _lECatDesc( new QLineEdit ),
    _lCatType( new QLabel( tr("Type:") ) ),
    _cbCatTypes( new QComboBox ),
    _wCatParams( new QWidget ),
    _tbCatParamsActions( new QToolBar ),
    _tvCatParams( new QTreeView ),
    _tableCatParamWidget( new QWidget ),
    _lTableCatName( new QLabel( tr("Name:") ) ),
    _lETableCatName( new QLineEdit ),
    _lTableCatCode( new QLabel( tr("Code:") ) ),
    _lETableCatCode( new QLineEdit ),
    _lTableCatDesc( new QLabel( tr("Description:") ) ),
    _lETableCatDesc( new QLineEdit ),
    _wTableCatParams( new QWidget ),
    _tbTableCatParamsActions( new QToolBar ),
    _tvTableCatParams( new QTreeView ) {
    init();
}

pCatEditor::~pCatEditor( ) {
    delete _tvTableCatParams;
    delete _tbTableCatParamsActions;
    delete _wTableCatParams;
    delete _lETableCatDesc;
    delete _lTableCatDesc;
    delete _lETableCatCode;
    delete _lTableCatCode;
    delete _lETableCatName;
    delete _lTableCatName;
    delete _tableCatParamWidget;
    delete _tvCatParams;
    delete _tbCatParamsActions;
    delete _wCatParams;
    delete _cbCatTypes;
    delete _lCatType;
    delete _lECatDesc;
    delete _lCatDesc;
    delete _lECatCode;
    delete _lCatCode;
    delete _lECatName;
    delete _lCatName;
    delete _catParamWidget;
    delete _tabCatWidget;
    delete _tbCatActions;
}

QSharedPointer< pCategory > pCatEditor::getCategory() const {
    return _pCategory;
}

void pCatEditor::setCategory( QSharedPointer< pCategory > pc ) {
    _pCategory = pc;
    initValues();
}

void pCatEditor::saveCategory( ) {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::addParamIntoCat() {
    qDebug() << __PRETTY_FUNCTION__;
    emit addParameterIntoCategory( _pCategory, _tvCatParams->model() );
}

void pCatEditor::removeParamFromCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::addParamIntoTableCat() {
    qDebug() << __PRETTY_FUNCTION__;
    if ( !_pCategory.isNull() && !_pCategory->getTableCat().isNull() )
        emit addParameterIntoCategory( _pCategory->getTableCat(), _tvTableCatParams->model() );
}

void pCatEditor::removeParamFromTableCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::init( ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _tbCatActions, 0, 0, 1, 1 );
    grLay->addWidget( _tabCatWidget, 1, 0, 1, 1 );
    _tabCatWidget->addTab( _catParamWidget, tr("Category") );
    QGridLayout* grCatParamLay = new QGridLayout ( _wCatParams );
    grCatParamLay->addWidget( _tbCatParamsActions, 0, 0, 1, 1 );
    grCatParamLay->addWidget( _tvCatParams, 1, 0, 1, 1 );
    _tabCatWidget->addTab( _wCatParams, tr("Parameters of category") );
    _tabCatWidget->addTab( _tableCatParamWidget, tr("Table category") );
    QGridLayout* grTableCatParamLay = new QGridLayout( _wTableCatParams );
    grTableCatParamLay->addWidget( _tbTableCatParamsActions, 0, 0, 1, 1 );
    grTableCatParamLay->addWidget( _tvTableCatParams, 1, 0, 1, 1 );
    _tabCatWidget->addTab( _wTableCatParams, tr("Parameters of table category") );

    initActions();
    initCatParams();
    initTableCatParams();
    initValues();
}

void pCatEditor::initActions( ) {
    QAction* actAddParam = _tbCatParamsActions->addAction(QIcon(":/patrol/add_parameter_to_cat.svg"), tr("Add parameter to category") );
    actAddParam->setToolTip( tr("Add parameter to main category") );
    QObject::connect( actAddParam, &QAction::triggered, this, &pCatEditor::addParamIntoCat );

    QAction* actRemoveParam = _tbCatParamsActions->addAction(QIcon(":/patrol/remove_parameter_from_cat.svg"), tr("Remove parameter from category") );
    actRemoveParam->setToolTip( tr("Remove parameter from main category") );
    QObject::connect( actRemoveParam, &QAction::triggered, this, &pCatEditor::removeParamFromCat );

    QAction* actUpParam = _tbCatParamsActions->addAction(QIcon(":/patrol/up_arrow.svg"), tr( "Up" ) );
    actUpParam->setToolTip( tr("Increase parameter order") );
    QObject::connect( actUpParam, &QAction::triggered, this, &pCatEditor::upParamInCat );
    QAction* actDownParam = _tbCatParamsActions->addAction( QIcon(":/patrol/down_arrow.svg"), tr ( "Down" ) );
    actDownParam->setToolTip( tr("Decrease parameter order") );
    QObject::connect( actDownParam, &QAction::triggered, this, &pCatEditor::downParamInCat );

    QAction* actAddTableParam = _tbTableCatParamsActions->addAction( QIcon(":/patrol/add_parameter_to_cat.svg"), tr( "Add parameter to table category" ) );
    actAddParam->setToolTip( tr("Add parameter to table category") );
    QObject::connect( actAddTableParam, &QAction::triggered, this, &pCatEditor::addParamIntoTableCat );

    QAction* actRemoveTableParam = _tbTableCatParamsActions->addAction( QIcon(":/patrol/remove_parameter_from_cat.svg"), tr("Remove parameter from table category") );
    actRemoveTableParam->setToolTip( tr("Remove parameter from table category") );
    QObject::connect( actRemoveTableParam, &QAction::triggered, this, &pCatEditor::removeParamFromTableCat );

    QAction* actUpTableParam = _tbTableCatParamsActions->addAction( QIcon(":/patrol/up_arrow.svg"), tr( "Up" ) );
    actUpTableParam->setToolTip( tr("Increase parameter order") );
    QObject::connect( actUpTableParam, &QAction::triggered, this, &pCatEditor::upParamInTableCat );
    QAction* actDownTableParam = _tbTableCatParamsActions->addAction( QIcon(":/patrol/down_arrow.svg"), tr ( "Down" ) );
    actDownTableParam->setToolTip( tr("Decrease parameter order") );
    QObject::connect( actDownTableParam, &QAction::triggered, this, &pCatEditor::downParamInTableCat );

    QAction* actSaveCat = _tbCatActions->addAction( QIcon(":/patrol/save_db.png"), tr ("Save categories to DB") );
    actSaveCat->setToolTip( tr("Save categories to database") );
    QObject::connect( actSaveCat, &QAction::triggered, this, &pCatEditor::saveCategory );
}

void pCatEditor::initCatParams( ) {
    QGridLayout * grCatPLay = new QGridLayout( _catParamWidget );

    QHBoxLayout* hNameLay = new QHBoxLayout;
    hNameLay->addWidget( _lCatName );
    hNameLay->addWidget( _lECatName );
    grCatPLay->addLayout( hNameLay, 0, 0, 1, 1, Qt::AlignJustify);

    QHBoxLayout* hCodeLay = new QHBoxLayout;
    hCodeLay->addWidget( _lCatCode );
    hCodeLay->addWidget( _lECatCode );
    grCatPLay->addLayout( hCodeLay, 1, 0, 1, 1, Qt::AlignJustify);

    QHBoxLayout* hDescLay = new QHBoxLayout;
    hDescLay->addWidget( _lCatDesc );
    hDescLay->addWidget( _lECatDesc );
    grCatPLay->addLayout( hDescLay, 2, 0, 1, 1, Qt::AlignJustify );
    
    QHBoxLayout* hCTypeLay = new QHBoxLayout;
    hCTypeLay->addWidget( _lCatType );
    hCTypeLay->addWidget( _cbCatTypes );
    grCatPLay->addLayout( hCTypeLay, 3, 0, 1, 1, Qt::AlignJustify);
}

void pCatEditor::initTableCatParams( ) {
    QGridLayout* grTableCatLay = new QGridLayout( _tableCatParamWidget );

    QHBoxLayout* hTNameLay = new QHBoxLayout;
    hTNameLay->addWidget( _lTableCatName );
    hTNameLay->addWidget( _lETableCatName );
    grTableCatLay->addLayout( hTNameLay, 0, 0, 1, 1, Qt::AlignJustify );

    QHBoxLayout* hTCodeLay = new QHBoxLayout;
    hTCodeLay->addWidget( _lTableCatCode );
    hTCodeLay->addWidget( _lETableCatCode );
    grTableCatLay->addLayout( hTCodeLay, 1, 0, 1, 1, Qt::AlignJustify );
    QHBoxLayout* hTDescLay = new QHBoxLayout;
    hTDescLay->addWidget( _lTableCatDesc );
    hTDescLay->addWidget( _lETableCatDesc );
    grTableCatLay->addLayout( hTDescLay, 2, 0, 1, 1, Qt::AlignJustify | Qt::AlignTop );
}

void pCatEditor::initValues( ) {
    _cbCatTypes->clear();
    for( QMap< qint64, QSharedPointer< pCategoryType > >::const_iterator pct = _availCatTypes.constBegin();
            pct != _availCatTypes.constEnd();
            pct++ ) {
        _cbCatTypes->addItem( pct.value()->getName(), pct.key() );
    }
    qint64 idDefType = (_pCategory.isNull() ? 1 : _pCategory->getType()->getId());
    int typeInd = _cbCatTypes->findData( idDefType );
    _cbCatTypes->setCurrentIndex( typeInd );
    bool isTypeCh = (_pCategory.isNull() || _pCategory->getId() <= 0);
    _cbCatTypes->setEnabled( isTypeCh );

    QRegExp cRegExp(QString("[A-Za-z0-9_]*"));
    QValidator* codeVal = new QRegExpValidator(cRegExp, this);
    _lECatName->setText( _pCategory->getName() );
    _lECatCode->setText( _pCategory->getCode() );
    _lECatCode->setValidator( codeVal );
    _lECatDesc->setText( _pCategory->getDesc() );
    if( !_pCategory->getTableCat().isNull() ) {
        QSharedPointer< pCategory > pCatT = _pCategory->getTableCat();
        _lETableCatName->setText( pCatT->getName() );
        _lETableCatCode->setText( pCatT->getCode() );
        QValidator* tCodeVal = new QRegExpValidator(cRegExp, this);
        _lETableCatCode->setValidator( tCodeVal );
        _lETableCatDesc->setText( pCatT->getDesc() );
    }
}

void pCatEditor::setCatParamModel( QAbstractItemModel* paramModel ) {
    QAbstractItemModel* oldModel = _tvCatParams->model();
    _tvCatParams->setModel( paramModel );
    if (oldModel && oldModel != paramModel )
        delete oldModel;
}

void pCatEditor::setTableCatParamModel( QAbstractItemModel* paramModel ) {
    QAbstractItemModel* oldModel = _tvTableCatParams->model();
    _tvTableCatParams->setModel( paramModel );
    if (oldModel && oldModel != paramModel )
        delete oldModel;
}

void pCatEditor::upParamInCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::downParamInCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::upParamInTableCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::downParamInTableCat() {
    qDebug() << __PRETTY_FUNCTION__;
}
