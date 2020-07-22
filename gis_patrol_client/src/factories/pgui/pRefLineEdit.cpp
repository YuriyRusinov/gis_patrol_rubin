/*
 * @brief Класс-виджет для параметров вида элемент справочника и родитель-потомок
 * pRefLineEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pRefLineEdit.h"

pRefLineEdit::pRefLineEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags)
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _pLEValue( new QLineEdit ),
    _tbParam( new QToolButton ) {
    setup();
    _pLEValue->setText( pValue->getColumnValue() );
}

pRefLineEdit::~pRefLineEdit() {
    delete _tbParam;
    delete _pLEValue;
    delete _lParam;
}

void pRefLineEdit::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    hLay->addWidget( _lParam, 0, Qt::AlignRight | Qt::AlignVCenter );
    hLay->addWidget( _pLEValue );
    hLay->addWidget( _tbParam );
    _pLEValue->setReadOnly( true );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    _tbParam->setText( QString("...") );
    QObject::connect( _tbParam, &QToolButton::clicked, this, &pRefLineEdit::changeRef );
}

void pRefLineEdit::setParamValue( QSharedPointer< pParamValue > pValue ) {
    pAbstractParamWidget::setParamValue( pValue );
    _pLEValue->setText( pValue->getColumnValue() );
    emit valueChanged( pValue );
}

void pRefLineEdit::changeRef() {
    QSharedPointer< pParamValue > pValue = this->paramValue();
    emit changeRecord( pValue, _pLEValue );
}

void pRefLineEdit::setReadOnly( bool value ) {
    _tbParam->setEnabled( !value );
}
