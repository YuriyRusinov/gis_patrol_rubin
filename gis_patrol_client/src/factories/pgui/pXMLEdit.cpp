/*
 * @brief Класс виджета, работающий с xml
 * pXMLEdit.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QGridLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QLabel>
#include <QMessageBox>
#include <QXmlStreamReader>
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
    QString xmlFileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("XML files (*.xml);;All files (*.*)") );
    if( xmlFileName.isEmpty() )
        return;
    QFile xmlFile( xmlFileName );
    bool isOpenOk = xmlFile.open( QIODevice::ReadOnly );
    if( !isOpenOk ) {
        QMessageBox::warning( this, tr("Open xml file"), tr( "Cannot open xml file %1 for reading" ).arg( xmlFileName ), QMessageBox::Ok );
        return;
    }
    QXmlStreamReader xmlStream( &xmlFile );
    QStringList elements;
    while( !xmlStream.atEnd() ) {
        QXmlStreamReader::TokenType tType = xmlStream.readNext();
        QString tString = xmlStream.tokenString();
        //QString xmlStr = xmlStream.readElementText();
        //elements.append( xmlStr );
        qDebug() << __PRETTY_FUNCTION__ << tType << tString;
    }
}
