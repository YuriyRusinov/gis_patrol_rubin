/*
 * @brief Класс-виджет для даты
 * pDateEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QDate>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QLabel>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pDateEdit.h"

pDateEdit::pDateEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _pDE( new QDateEdit( pValue->value().isNull() || QString::compare( pValue->value().toString(), QString("current_date"), Qt::CaseInsensitive ) ==0 || pValue->value().toString().isEmpty() ? QDate::currentDate() : pValue->value().toDate() ) ) {
    setup();
}

pDateEdit::~pDateEdit() {
    delete _pDE;
    delete _lParam;
}

void pDateEdit::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    hLay->addWidget( _lParam, 0, Qt::AlignRight | Qt::AlignVCenter );
    hLay->addWidget( _pDE );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    QObject::connect( _pDE, &QDateEdit::dateChanged, this, &pDateEdit::pDateChanged );
}

void pDateEdit::pDateChanged( const QDate &date ) {
    paramValue()->setValue( QVariant(date) );
    emit valueChanged( paramValue() );
}

void pDateEdit::setReadOnly( bool value ) {
    _pDE->setEnabled( !value );
}
