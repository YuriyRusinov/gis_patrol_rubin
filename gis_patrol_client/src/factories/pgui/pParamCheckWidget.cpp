/* 
 * @brief Класс для отображения параметра типа "набор элементов справочника"
 * pParamCheckWidget.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAbstractItemModel>
#include <QGridLayout>
#include <QLabel>
#include <QTreeView>
#include <QtDebug>

#include <pCatParameter.h>
#include <pParamValue.h>

#include "pParamCheckWidget.h"

pParamCheckWidget::pParamCheckWidget( QSharedPointer< pParamValue > pValue, QAbstractItemModel* valuesModel, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _lParam( new QLabel( pValue->getCatParam()->getTitle() ) ),
    _tvValues( new QTreeView ) {
    _tvValues->setModel( valuesModel );
    setup();
    QObject::connect( valuesModel, &QAbstractItemModel::dataChanged, this, &pParamCheckWidget::dataValueChanged );
}

pParamCheckWidget::~pParamCheckWidget() {
    delete _lParam;
    delete _tvValues;
}

void pParamCheckWidget::setReadOnly( bool value ) {
    //
    //TODO: необходим подходящий делегат
    //
    Q_UNUSED( value );
}

void pParamCheckWidget::dataValueChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight ) {
    //
    // Debug output
    //
    qDebug() << __PRETTY_FUNCTION__ << topLeft << bottomRight << paramValue()->value() << paramValue()->value().isNull() << paramValue()->valueForInsert();
}

void pParamCheckWidget::setup( ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _lParam, 0, 0, 1, 1, Qt::AlignTop );
    grLay->addWidget( _tvValues, 0, 1, 2, 1, Qt::AlignLeft | Qt::AlignTop );
}
