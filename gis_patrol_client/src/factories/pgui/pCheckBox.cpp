/*
 * @brief Класс-виджет для логических параметров
 * pCheckBox.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QCheckBox>
#include <QHBoxLayout>

#include <pParamValue.h>
#include <pCatParameter.h>
#include "pCheckBox.h"

pCheckBox::pCheckBox( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags  ) :
    pAbstractParamWidget( pValue, parent, flags ), _pcbVal( new QCheckBox (pValue->getCatParam()->getTitle() ) ) {
    setup();
}

pCheckBox::~pCheckBox() {
    delete _pcbVal;
}

void pCheckBox::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    hLay->addWidget( _pcbVal );
    QSharedPointer< pParamValue > pValue = pAbstractParamWidget::paramValue();
    _pcbVal->setCheckState( pValue->value().toBool() ? Qt::Checked : Qt::Unchecked );
    QObject::connect( _pcbVal, &QCheckBox::stateChanged, this, &pCheckBox::pStateChanged );
}

void pCheckBox::pStateChanged( int state ) {
    QSharedPointer< pParamValue > pValue = pAbstractParamWidget::paramValue();
    bool st = ( state == Qt::Checked );
    pValue->setValue( QVariant(st) );
    emit valueChanged( pValue );
}
