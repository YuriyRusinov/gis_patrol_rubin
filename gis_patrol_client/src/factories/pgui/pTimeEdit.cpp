/*
 * @brief Класс-виджет для времени
 * pTimeEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QTime>
#include <QTimeEdit>
#include <QHBoxLayout>
#include <QLabel>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pTimeEdit.h"

pTimeEdit::pTimeEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _pTE( new QTimeEdit( pValue->value().isNull() || QString::compare( pValue->value().toString(), QString("current_time"), Qt::CaseInsensitive ) ==0 || pValue->value().toString().isEmpty() ? QTime::currentTime() : pValue->value().toTime() ) ) {
    setup();
}

pTimeEdit::~pTimeEdit() {
    delete _pTE;
    delete _lParam;
}

void pTimeEdit::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    hLay->addWidget( _lParam, 0, Qt::AlignRight | Qt::AlignVCenter );
    hLay->addWidget( _pTE );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    QObject::connect( _pTE, &QTimeEdit::timeChanged, this, &pTimeEdit::pTimeChanged );
}

void pTimeEdit::pTimeChanged( const QTime &time ) {
    paramValue()->setValue( QVariant(time) );
    emit valueChanged( paramValue() );
}

void pTimeEdit::setReadOnly( bool value ) {
    _pTE->setEnabled( !value );
}
