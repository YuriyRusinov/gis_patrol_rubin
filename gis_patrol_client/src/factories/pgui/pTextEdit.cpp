/*
 * @brief Класс-виджет для текстового поля
 * pTextEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>

#include <pParamValue.h>
#include <pCatParameter.h>
#include "pTextEdit.h"

pTextEdit::pTextEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _pTextE( new QTextEdit( pValue->value().toString() ) ) {
    setup( );
}

pTextEdit::~pTextEdit() {
    delete _pTextE;
    delete _lParam;
}

void pTextEdit::setup( ) {
    QGridLayout* gLay = new QGridLayout( this );
    gLay->addWidget( _lParam, 0, 0, 2, 1, Qt::AlignRight | Qt::AlignTop );
    gLay->addWidget( _pTextE, 0, 1, 2, 1, Qt::AlignLeft | Qt::AlignVCenter );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    QObject::connect( _pTextE, &QTextEdit::textChanged, this, &pTextEdit::pTextChanged );
}

void pTextEdit::pTextChanged() {
    paramValue()->setValue( QVariant( _pTextE->toPlainText() ) );
    emit valueChanged( paramValue() );
}
