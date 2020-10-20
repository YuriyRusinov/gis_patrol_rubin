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
#include <QGridLayout>
#include <QLabel>
#include <QTableView>
#include <QToolButton>
#include <QVBoxLayout>

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
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _lParam, 0, 0, 1, 1 );
    QStringList strGeomTypes;
    strGeomTypes << tr("Point")
                 << tr("MultiPoint")
                 << tr("LineString")
                 << tr("MultiLineString")
                 << tr("Polygon")
                 << tr("MultiPolygon");
    for( int i=pPoint; i <= pMultiPolygon; i++ ) {
        _cbGeomType->addItem(strGeomTypes[i], i);
    }
    grLay->addWidget( _cbGeomType, 0, 1, 1, 1 );
    QGridLayout* grPointsLay = new QGridLayout; 
    grPointsLay->addWidget( _tvPoints, 0, 0, 1, 1 );
    QVBoxLayout* vButtonsLay = new QVBoxLayout;
    vButtonsLay->addWidget( _tbAddPoint );
    vButtonsLay->addWidget( _tbRemovePoint );
    vButtonsLay->addStretch();
    grPointsLay->addLayout( vButtonsLay, 0, 1, 1, 1 );
    grLay->addLayout( grPointsLay, 1, 0, 1, 2 );
    _tbAddPoint->setText( tr("...") );
    _tbAddPoint->setToolTip( tr("Add point to geometry") );
    _tbRemovePoint->setText( tr("...") );
    _tbRemovePoint->setToolTip( tr("Remove point from geometry") );

    QObject::connect( _cbGeomType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&pGeomForm::geomTypeChanged) );
    QObject::connect( _tbAddPoint, &QAbstractButton::clicked, this, &pGeomForm::addPoint );
    QObject::connect( _tbRemovePoint, &QAbstractButton::clicked, this, &pGeomForm::removePoint );
}

void pGeomForm::geomTypeChanged( int gType ) {
    qDebug() << __PRETTY_FUNCTION__ << gType;
}

void pGeomForm::addPoint() {
    qDebug() << __PRETTY_FUNCTION__;
}

void pGeomForm::removePoint() {
    qDebug() << __PRETTY_FUNCTION__;
}
