/* 
 * @brief Класс для отображения параметра типа "набор элементов справочника"
 * pParamCheckWidget.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QGridLayout>
#include <QTreeView>
#include <QtDebug>
#include "pParamCheckWidget.h"

pParamCheckWidget::pParamCheckWidget( QSharedPointer< pParamValue > pValue, QWidget* parent, Qt::WindowFlags flags )
    : pAbstractParamWidget( pValue, parent, flags ),
    _tvValues( new QTreeView ) {
    setup();
}

pParamCheckWidget::~pParamCheckWidget() {
    delete _tvValues;
}

void pParamCheckWidget::setReadOnly( bool value ) {
    //
    //TODO: необходим подходящий делегат
    //
    Q_UNUSED( value );
}

void pParamCheckWidget::dataValueChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight ) {
    qDebug() << __PRETTY_FUNCTION__ << topLeft << bottomRight;
    //
    //TODO: написать соответствующий функционал.
    //
    Qt::CheckState chState = (Qt::CheckState)(topLeft.data( Qt::CheckStateRole ).toInt());
    if( chState == Qt::Checked ) {
    }
}

void pParamCheckWidget::setup( ) {
    QGridLayout* grLay = new QGridLayout( this );
    grLay->addWidget( _tvValues, 0, 0, 1, 1 );
}
