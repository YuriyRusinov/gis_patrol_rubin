/*
 * @brief Класс форма поиска в таблице информационного объекта
 * psearchform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QAction>
#include <pCategory.h>
#include <pParameter.h>

#include "psearchform.h"
#include "ui_p_search_form.h"

pSearchForm::pSearchForm( QSharedPointer< pCategory > pSearchCategory,
                          const QString& tableName,
                          const QMap<qint64, QSharedPointer< pParameter > >& pParams,
                          QWidget* parent,
                          Qt::WindowFlags flags )
    : QDialog( parent, flags ),
    _UI( new Ui::p_search_form ),
    _delSearchEntity( new QAction (this) )
 {
    _UI->setupUi( this );
    Q_UNUSED( pSearchCategory );
    Q_UNUSED( tableName );
    Q_UNUSED( pParams );
    QKeySequence dKey( Qt::Key_Delete );//QKeySequence::Delete);
    _delSearchEntity->setShortcut( dKey );
    addAction( _delSearchEntity );

    QObject::connect ( _UI->pbOK, &QPushButton::clicked, this, &pSearchForm::saveSQLAccept );
    QObject::connect ( _UI->pbCancel, &QPushButton::clicked, this, &QDialog::reject );
}

pSearchForm::~pSearchForm( ) {
    delete _UI;
}

void pSearchForm::saveSQLAccept( ) {

    QDialog::accept();
}
