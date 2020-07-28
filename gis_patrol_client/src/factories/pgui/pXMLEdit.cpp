/*
 * @brief Класс виджета, работающий с xml
 * pXMLEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QFileDialog>
#include <QFont>
#include <QGridLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QLabel>
#include <QtDebug>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pXMLEdit.h"

pXMLEdit::pXMLEdit( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _xmlTE( new QTextEdit( pValue->value().toString() ) ),
    _tbXml( new QToolButton ) {
    setup();
}

pXMLEdit::~pXMLEdit( ) {
    delete _tbXml;
    delete _xmlTE;
    delete _lParam;
}

void pXMLEdit::setReadOnly( bool value ) {
    _tbXml->setEnabled( !value );
    _xmlTE->setEnabled( !value );
}

void pXMLEdit::setup( ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _lParam, 0, 0, 2, 1, Qt::AlignRight | Qt::AlignTop );
    grLay->addWidget( _xmlTE, 0, 1, 2, 1, Qt::AlignLeft | Qt::AlignVCenter );
    grLay->addWidget( _tbXml, 0, 2, 2, 1, Qt::AlignLeft | Qt::AlignTop );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    QObject::connect( _tbXml, &QToolButton::clicked, this, &pXMLEdit::loadXml );
}

void pXMLEdit::loadXml() {
    qDebug() << __PRETTY_FUNCTION__;
}
