/*
 * @brief Класс-виджет для логических параметров
 * pCheckBox.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QHBoxLayout>

#include <pParamValue.h>
#include "pCheckBox.h"

pCheckBox::pCheckBox( QSharedPointer< pParamValue > pValue, QWidget* parent  ) :
    QCheckBox( parent ),
    pAbstractParamWidget( pValue ) {
    setup();
}

pCheckBox::~pCheckBox() {
}

void pCheckBox::setup( ) {
    QHBoxLayout* hLay = new QHBoxLayout( this );
    setLayout( hLay );
    QObject::connect( this, &QCheckBox::stateChanged, this, &pCheckBox::pStateChanged );
}

void pCheckBox::pStateChanged( int state ) {
    QSharedPointer< pParamValue > pValue = pAbstractParamWidget::paramValue();
    bool st = ( state == Qt::Checked );
    pValue->setValue( QVariant(st) );
    emit valueChanged( pValue );
}
