/*
 * @brief Класс-виджет для параметров вида SVG
 * pSVGEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QGridLayout>
#include <QLabel>
#include <QSvgWidget>
#include <QToolButton>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pSVGEdit.h"

pSVGEdit::pSVGEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags)
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _svgWidget( new QSvgWidget ),
    _tbLoad( new QToolButton ) {
    setup();
}

pSVGEdit::~pSVGEdit() {
    delete _tbLoad;
    delete _svgWidget;
    delete _lParam;
}

void pSVGEdit::setReadOnly( bool value ) {
    _tbLoad->setEnabled( !value );
}

void pSVGEdit::openFile( ) {
}

void pSVGEdit::setup( ) {
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    _tbLoad->setText( QString("...") );
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _lParam, 0, 0, 2, 1, Qt::AlignRight | Qt::AlignTop );
    grLay->addWidget( _svgWidget, 0, 1, 2, 1, Qt::AlignCenter | Qt::AlignVCenter );
    grLay->addWidget( _tbLoad, 0, 2, 2, 1, Qt::AlignLeft | Qt::AlignTop );
    QObject::connect( _tbLoad, &QToolButton::clicked, this, &pSVGEdit::openFile );
}
