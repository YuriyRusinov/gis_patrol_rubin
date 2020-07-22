/*
 * @brief Класс-виджет для численных и строковых параметров
 * pLineEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pLineEdit.h"

pLineEdit::pLineEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _pLE( new QLineEdit( pValue->value().toString() ) ) {
    setup();
}

pLineEdit::~pLineEdit() {
    delete _pLE;
    delete _lParam;
}

void pLineEdit::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    hLay->addWidget( _lParam, 0, Qt::AlignRight | Qt::AlignVCenter );
    hLay->addWidget( _pLE );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    QObject::connect( _pLE, &QLineEdit::textChanged, this, &pLineEdit::pTextChanged );
}

void pLineEdit::pTextChanged(const QString& text) {
    paramValue()->setValue( QVariant(text) );
    emit valueChanged( paramValue() );
}

void pLineEdit::setValidator( QValidator* val ) {
    _pLE->setValidator( val );
}

void pLineEdit::setReadOnly( bool value ) {
    _pLE->setReadOnly( value );
}
