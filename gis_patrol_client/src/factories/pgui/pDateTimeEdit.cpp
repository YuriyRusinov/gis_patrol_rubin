/*
 * @brief Класс-виджет для даты-времени
 * pDateTimeEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QDateTime>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QtDebug>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pDateTimeEdit.h"

pDateTimeEdit::pDateTimeEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _pDTE( new QDateTimeEdit( pValue->value().isNull() || QString::compare( pValue->value().toString(), QString("current_timestamp"), Qt::CaseInsensitive ) ==0 || pValue->value().toString().isEmpty() ? QDateTime::currentDateTime() : pValue->value().toDateTime() ) ) {
    qDebug() << __PRETTY_FUNCTION__ << pValue->value();
    setup();
}

pDateTimeEdit::~pDateTimeEdit() {
    delete _pDTE;
    delete _lParam;
}

void pDateTimeEdit::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    hLay->addWidget( _lParam, 0, Qt::AlignRight | Qt::AlignVCenter );
    hLay->addWidget( _pDTE );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    QObject::connect( _pDTE, &QDateEdit::dateTimeChanged, this, &pDateTimeEdit::pDateTimeChanged );
}

void pDateTimeEdit::pDateTimeChanged( const QDateTime &dateTime ) {
    paramValue()->setValue( QVariant(dateTime) );
    emit valueChanged( paramValue() );
}

void pDateTimeEdit::setReadOnly( bool value ) {
    _pDTE->setEnabled( !value );
}
