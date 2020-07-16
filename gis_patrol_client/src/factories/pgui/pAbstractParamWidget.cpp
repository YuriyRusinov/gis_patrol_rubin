/*
 * @brief Базовый класс для виджетов, работающих с параметрами записей в БД
 * pAbstractParamWidget.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <pParamValue.h>
#include "pAbstractParamWidget.h"

pAbstractParamWidget::pAbstractParamWidget( QSharedPointer< pParamValue > pValue) : //, QWidget* parent, Qt::WindowFlags flags ) :
//    QWidget( parent, flags ),
    _paramValue( pValue ) {
}

pAbstractParamWidget::~pAbstractParamWidget() {
}

QSharedPointer< const pParamValue > pAbstractParamWidget::paramValue() const {
    return _paramValue;
}

QSharedPointer< pParamValue > pAbstractParamWidget::paramValue() {
    return _paramValue;
}

void pAbstractParamWidget::setParamValue( QSharedPointer< pParamValue > pValue ) {
    _paramValue = pValue;
}

