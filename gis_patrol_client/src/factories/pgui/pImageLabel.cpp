/*
 * @brief Класс-виджет для параметров изображений
 * pImageLabel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <QBuffer>
#include <QFileDialog>
#include <QFont>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QToolButton>

#include <pCatParameter.h>
#include <pParamValue.h>
#include "pImageLabel.h"

pImageLabel::pImageLabel( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _px( QPixmap() ),
    _lImage( new QLabel ),
    _tbParam( new QToolButton ),
    _tbClear( new QToolButton ) {
    setup();
    _lImage->setPixmap( pValue->value().value< QPixmap >() );
}

pImageLabel::~pImageLabel() {
    delete _tbClear;
    delete _tbParam;
    delete _lImage;
    delete _lParam;
}

void pImageLabel::setReadOnly( bool value ) {
    _tbParam->setEnabled( !value );
}

void pImageLabel::setVal( const QString& newJpg ) {
    QVariant v( newJpg );
    QSharedPointer< pParamValue > pValue = this->paramValue();
    pValue->setValue( v );
}

void pImageLabel::openFile( ) {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image File"), 
                                                    QDir::currentPath(),
                                                    tr("Images (*.png *.xpm *.jpg *.PNG *.XPM *.JPG)"));

    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            qWarning() << tr("Cannot load %1.").arg(fileName);
            QMessageBox::information(this, tr("Error"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        _px = QPixmap::fromImage(image);
        setImagePrivate();

    }
    else{
        return;
    }

    QVariant v = _px;

    QSharedPointer< pParamValue > pValue = paramValue();
    pValue->setValue( v );
    qDebug() << __PRETTY_FUNCTION__ << pValue->value() << pValue->valueForInsert() << pValue->value().isNull();
    setParamValue( pValue );
    emit valueChanged( pValue );
}

void pImageLabel::setPixmap( const QString& contents ) {
    QByteArray ba = contents.toLocal8Bit();
    bool ok = _px.loadFromData( ba, "XPM");
    if(!ok){
        qWarning() << "Cannot construct QPixmap from raw data! XPM = " << contents;
        return;
    }
    setImagePrivate();
}

void pImageLabel::setup( ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _lParam, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignVCenter );
    grLay->addWidget( _lImage, 0, 1, 2, 1, Qt::AlignLeft | Qt::AlignTop );
    //_lImage->setFrameStyle( QFrame::Panel );
    QHBoxLayout* hButtonsLay = new QHBoxLayout;
    hButtonsLay->addWidget( _tbParam );
    hButtonsLay->addWidget( _tbClear );
    grLay->addLayout( hButtonsLay, 0, 2, 2, 1, Qt::AlignLeft | Qt::AlignTop );
    QFont lFont = _lParam->font();
    if( this->paramValue()->getCatParam()->isMandatory() ) {
        lFont.setBold( true );
        _lParam->setFont( lFont );
    }
    _tbParam->setText( QString("...") );
    _tbClear->setText( tr("Clear") );
    _tbClear->setToolTip( tr("Clear image") );
    QObject::connect( _tbParam, &QToolButton::clicked, this, &pImageLabel::openFile );
    QObject::connect( _tbClear, &QToolButton::clicked, this, &pImageLabel::clearImage );
}

const QPixmap& pImageLabel::pixmap() const {
    return _px;
}

QByteArray pImageLabel::save() {
    QByteArray bytes;
    QBuffer buffer(&bytes);

    buffer.open(QIODevice::WriteOnly);
    _px.save(&buffer, "XPM"); // writes pixmap into bytes in XPM format
    buffer.close();

    return bytes;
}

void pImageLabel::setImagePrivate( ) {
    int w = _px.width();
    int h = _px.height();

    this->_lImage->setPixmap(_px);

    this->_lImage->resize(w, h);
}

void pImageLabel::clearImage() {
    _px = QPixmap();
    QSharedPointer< pParamValue > pValue = paramValue();
    pValue->setValue( QVariant() );
    setParamValue( pValue );
    emit valueChanged( pValue );
    setImagePrivate();
}
