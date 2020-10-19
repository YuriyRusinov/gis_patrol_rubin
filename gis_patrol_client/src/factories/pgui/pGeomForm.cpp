/*
 * @brief Класс-виджет для параметров геометрического типа
 * pGeomForm.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <QComboBox>
#include <QLabel>
#include <QTableView>
#include <QToolButton>

#include <pParamValue.h>
#include <pCatParameter.h>
#include "pGeomForm.h"

pGeomForm::pGeomForm( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _cbGeomType( new QComboBox ),
    _tvPoints( new QTableView ),
    _tbAddPoint( new QToolButton ),
    _tbRemovePoint( new QToolButton ) {
    setup();
}

pGeomForm::~pGeomForm() {
    delete _tbRemovePoint;
    delete _tbAddPoint;
    delete _tvPoints;
    delete _cbGeomType;
    delete _lParam;
}

void pGeomForm::setReadOnly( bool value ) {
    _cbGeomType->setEnabled( !value );
    _tbAddPoint->setEnabled( !value );
    _tbRemovePoint->setEnabled( !value );
}

void pGeomForm::setup( ) {
}

void pGeomForm::geomTypeChanged() {
}

void pGeomForm::addPoint() {
}

void pGeomForm::removePoint() {

}
