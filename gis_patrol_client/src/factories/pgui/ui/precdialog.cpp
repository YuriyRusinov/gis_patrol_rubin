/*
 * @brief Класс-виджет для визуального отображения записей справочников
 * precdialog.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAbstractItemModel>
#include <QItemSelectionModel>

#include "pItemDelegate.h"
#include "ui_p_rec_dialog.h"
#include "precdialog.h"

pRecDialog::pRecDialog( QWidget* parent, Qt::WindowFlags flags )
    : QDialog( parent, flags ),
    _UI( new Ui::p_rec_dialog )
{
    _UI->setupUi( this );

    QAbstractItemDelegate* ideleg = new pItemDelegate;
    _UI->tvRecords->setItemDelegate( ideleg );

    QObject::connect( _UI->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );
    QObject::connect( _UI->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject );
}

pRecDialog::~pRecDialog() {
    delete _UI;
}

void pRecDialog::setRecModel( QAbstractItemModel* recModel ) {
    QAbstractItemModel* oldModel = _UI->tvRecords->model();
    _UI->tvRecords->setModel( recModel );
    if( oldModel && oldModel != recModel )
        delete oldModel;
}

qint64 pRecDialog::getRecId() const {
    QItemSelectionModel* selMod = _UI->tvRecords->selectionModel();
    if( !selMod || selMod->selectedIndexes().isEmpty() )
        return -1;

    QModelIndex wIndex = selMod->selectedIndexes().at( 0 );
    qint64 id = wIndex.isValid() ? wIndex.data( Qt::UserRole ).toLongLong() : -1;
    return id;
}
