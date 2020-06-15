/*
 * @brief Класс управляющий порядком просмотра-редактирования значения параметра узла связи,
 * в зависимости от его типа
 * pParamView.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pParamView.h"

pParamView::pParamView( qint64 id, QString name )
    : _id( id ),
    _name( name ) {
}

pParamView::pParamView( const pParamView& PV )
    : _id( PV._id ),
    _name( PV._name ) {
}

pParamView::~pParamView() {
}

qint64 pParamView::getId() const {
    return _id;
}

void pParamView::setId( qint64 id ) {
    _id = id;
}

QString pParamView::getName() const {
    return _name;
}

void pParamView::setName( QString name ) {
    _name = name;
}
