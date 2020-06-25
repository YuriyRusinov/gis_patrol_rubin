/*
 * @brief Данный класс унаследован от QWidget и предназначен для визуализации и редактирования категории
 * pCatEditor.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAction>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
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
    _tvCatParams( new QTreeView ),
    _tableCatParamWidget( new QWidget ),
    _lTableCatName( new QLabel( tr("Name:") ) ),
    _lETableCatName( new QLineEdit ),
    _lTableCatCode( new QLabel( tr("Code:") ) ),
    _lETableCatCode( new QLineEdit ),
    _lTableCatDesc( new QLabel( tr("Description:") ) ),
    _lETableCatDesc( new QLineEdit ),
    _tvTableCatParams( new QTreeView ) {
    init();
}

pCatEditor::~pCatEditor( ) {
    delete _tvTableCatParams;
    delete _lETableCatDesc;
    delete _lTableCatDesc;
    delete _lETableCatCode;
    delete _lTableCatCode;
    delete _lETableCatName;
    delete _lTableCatName;
    delete _tableCatParamWidget;
    delete _tvCatParams;
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
}

void pCatEditor::saveCategory( ) {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::addParamIntoCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::removeParamFromCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::addParamIntoTableCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::removeParamFromTableCat() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pCatEditor::init( ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _tbCatActions, 0, 0, 1, 1 );
    grLay->addWidget( _tabCatWidget, 1, 0, 1, 1 );
    _tabCatWidget->addTab( _catParamWidget, tr("Category") );
    _tabCatWidget->addTab( _tvCatParams, tr("Parameters of category") );
    _tabCatWidget->addTab( _tableCatParamWidget, tr("Table category") );
    _tabCatWidget->addTab( _tvTableCatParams, tr("Parameters of table category") );

    initActions();
    initCatParams();
    initTableCatParams();
}

void pCatEditor::initActions( ) {
    QAction* actAddParam = _tbCatActions->addAction(QIcon(":/patrol/add_parameter_to_cat.svg"), tr("Add parameter to category") );
    actAddParam->setToolTip( tr("Add parameter to main category") );
    QObject::connect( actAddParam, &QAction::triggered, this, &pCatEditor::addParamIntoCat );

    QAction* actRemoveParam = _tbCatActions->addAction(QIcon(":/patrol/remove_parameter_from_cat.svg"), tr("Remove parameter from category") );
    actRemoveParam->setToolTip( tr("Remove parameter from main category") );
    QObject::connect( actRemoveParam, &QAction::triggered, this, &pCatEditor::removeParamFromCat );

    _tbCatActions->addSeparator();

    QAction* actAddTableParam = _tbCatActions->addAction( QIcon(":/patrol/add_parameter_to_cat.svg"), tr( "Add parameter to table category" ) );
    actAddParam->setToolTip( tr("Add parameter to table category") );
    QObject::connect( actAddTableParam, &QAction::triggered, this, &pCatEditor::addParamIntoTableCat );

    QAction* actRemoveTableParam = _tbCatActions->addAction( QIcon(":/patrol/remove_parameter_from_cat.svg"), tr("Remove parameter from table category") );
    actRemoveTableParam->setToolTip( tr("Remove parameter from table category") );
    QObject::connect( actRemoveTableParam, &QAction::triggered, this, &pCatEditor::removeParamFromTableCat );
    _tbCatActions->addSeparator();

    QAction* actSaveCat = _tbCatActions->addAction( QIcon(":/patrol/save_db.png"), tr ("Save categories to DB") );
    actSaveCat->setToolTip( tr("Save categories to database") );
    QObject::connect( actSaveCat, &QAction::triggered, this, &pCatEditor::saveCategory );
}

void pCatEditor::initCatParams( ) {
    QGridLayout * grCatPLay = new QGridLayout( _catParamWidget );
    grCatPLay->addWidget( _lCatName, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grCatPLay->addWidget( _lECatName, 0, 1, 1, 1 , Qt::AlignLeft | Qt::AlignVCenter );
    grCatPLay->addWidget( _lCatCode, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grCatPLay->addWidget( _lECatCode, 1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter );
    grCatPLay->addWidget( _lCatDesc, 2, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grCatPLay->addWidget( _lECatDesc, 2, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter );
    grCatPLay->addWidget( _lCatType, 3, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grCatPLay->addWidget( _cbCatTypes, 3, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter );
}

void pCatEditor::initTableCatParams( ) {
    QGridLayout* grTableCatLay = new QGridLayout( _tableCatParamWidget );
    grTableCatLay->addWidget( _lTableCatName, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grTableCatLay->addWidget( _lETableCatName, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter );
    grTableCatLay->addWidget( _lTableCatCode, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grTableCatLay->addWidget( _lETableCatCode, 1, 1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter );
    grTableCatLay->addWidget( _lTableCatDesc, 2, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grTableCatLay->addWidget( _lETableCatDesc, 2, 1, 1, 1,  Qt::AlignLeft | Qt::AlignVCenter );
}
