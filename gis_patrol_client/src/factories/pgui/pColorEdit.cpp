/*
 * @brief Класс виджет для цвета фона.
 * pColorEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QBrush>
#include <QColor>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QWidget>
#include <QToolButton>

#include <pCatParameter.h>
#include <pParamValue.h>
#include <pParamType.h>

#include "pColorEdit.h"

pColorEdit::pColorEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _lColorLabel( new QLabel( tr("Sample text") ) ),
    _tbColor( new QToolButton ) {
    setup();
}

pColorEdit::~pColorEdit() {
    delete _tbColor;
    delete _lColorLabel;
    delete _lParam;
}

void pColorEdit::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    hLay->addWidget( _lParam, 0, Qt::AlignRight | Qt::AlignVCenter );
    hLay->addWidget( _lColorLabel, 0, Qt::AlignHCenter );
    hLay->addWidget( _tbColor );
    _tbColor->setText( tr("...") );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    QObject::connect( _tbColor, &QToolButton::clicked, this, &pColorEdit::setColor );

}

void pColorEdit::setColor() {
    QSharedPointer< pParamValue > pValue = paramValue();
    QColor newCol = QColorDialog::getColor( pValue->value().value<QColor>() );
    if( !newCol.isValid() ) {
        _lColorLabel->setAutoFillBackground( false );
        return;
    }
    _lColorLabel->setAutoFillBackground( true );
    pValue->setValue( QVariant( newCol ) );
    if( paramValue()->getCatParam()->getParamType()->getId() == pParamType::atRecordColor ||
        paramValue()->getCatParam()->getParamType()->getId() == pParamType::atRecordColorRef ) {
        QPalette bgPal = _lParam->palette();
        QBrush wBrush( newCol );
        bgPal.setBrush( QPalette::Window, wBrush );
        _lColorLabel->setPalette( bgPal );
    }
    else if ( paramValue()->getCatParam()->getParamType()->getId() == pParamType::atRecordTextColor ||
        paramValue()->getCatParam()->getParamType()->getId() == pParamType::atRecordTextColorRef ) {
        QColor fgCol( newCol);
        QPalette pal = _lParam->palette ();
        pal.setColor( QPalette::WindowText, fgCol );
        _lColorLabel->setPalette( pal );
    }
    emit valueChanged( pValue );
}
