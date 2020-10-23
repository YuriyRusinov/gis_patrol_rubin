/*
 * @brief Класс-виджет для параметров вида SVG
 * pSVGWidget.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QBuffer>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPicture>
#include <QSvgWidget>
#include <QToolButton>
#include <QtDebug>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pSVGWidget.h"

pSVGWidget::pSVGWidget( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags)
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _svgWidget( new QSvgWidget ),
    _tbLoad( new QToolButton ),
    _SVGContents( pValue->value().toByteArray() ) {
    setup();
}

pSVGWidget::~pSVGWidget() {
    delete _tbLoad;
    delete _svgWidget;
    delete _lParam;
}

void pSVGWidget::setReadOnly( bool value ) {
    _tbLoad->setEnabled( !value );
}

void pSVGWidget::openFile( ) {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image File"), 
                                                    QDir::currentPath(),
                                                    tr("SVG files (*.svg *.svgz *.svg.gz)"));

    if (fileName.isEmpty())
        return;

    QPicture pic;
    pic.load (fileName);
    if (pic.isNull())
    {
        qCritical() << tr("Cannot load %1.").arg(fileName);
        QMessageBox::critical(this, tr("Error"),
                                 tr("Cannot load %1.").arg(fileName));
        return;
    }
    QBuffer buffer (&_SVGContents);
    buffer.open (QIODevice::WriteOnly);
    pic.save (&buffer);
    _svgWidget->load( _SVGContents );
    QSharedPointer< pParamValue > pVal = paramValue();
    QVariant val( _SVGContents );
    pVal->setValue( val );
    setParamValue( pVal );
    emit valueChanged( pVal );
}

void pSVGWidget::setup( ) {
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    _tbLoad->setText( tr("...") );
    _svgWidget->load( _SVGContents );
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _lParam, 0, 0, 2, 1, Qt::AlignRight | Qt::AlignTop );
    grLay->addWidget( _svgWidget, 0, 1, 2, 1, Qt::AlignCenter | Qt::AlignVCenter );
    grLay->addWidget( _tbLoad, 0, 2, 2, 1, Qt::AlignLeft | Qt::AlignTop );
    QObject::connect( _tbLoad, &QToolButton::clicked, this, &pSVGWidget::openFile );
}
