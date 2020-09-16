/*
 * @brief Класс форма поиска в таблице информационного объекта
 * psearchform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QAction>
#include <QLabel>
#include <QComboBox>
#include <QStackedLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QTextEdit>
#include <QDateEdit>
#include <QDateTimeEdit>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QAbstractItemModel>
#include <QImage>
#include <QToolButton>
#include <QPushButton>

#include <pCategory.h>
#include <pParameter.h>

#include "pEventFilter.h"
#include "psearchform.h"
#include "ui_p_search_form.h"

pSearchForm::pSearchForm( QSharedPointer< pCategory > pSearchCategory,
                          const QString& tableName,
                          const QMap<qint64, QSharedPointer< pParameter > >& pParams,
                          QWidget* parent,
                          Qt::WindowFlags flags )
    : QDialog( parent, flags ),
    _UI( new Ui::p_search_form ),
    _delSearchEntity( new QAction (this) ),
    _pSearchCat( pSearchCategory ),
    _paramsIO( pParams ),
    _parentTable( tableName ) {
    _UI->setupUi( this );
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

QList< QSharedPointer< const pFilterGroup > >& pSearchForm::filters() {
    return _filters;
}

void pSearchForm::setFilters( const QList< QSharedPointer< const pFilterGroup > >& filters ) {
    _filters = filters;
}

void pSearchForm::init() {
}

void pSearchForm::initFilterTypes( pParamType::PatrolParamTypes type ) {
    Q_UNUSED( type );
}

void pSearchForm::initAttrs() {
}

void pSearchForm::initValuesWidgets( ) {
}

void pSearchForm::createGroup( bool AND ) {
    Q_UNUSED( AND );
}

void pSearchForm::updateSQL () {
}

void pSearchForm::setFiltersModel( QAbstractItemModel * mod, const QModelIndex& parent, QSharedPointer< const pFilterGroup > parentGroup ) {
    Q_UNUSED( mod );
    Q_UNUSED( parent );
    Q_UNUSED( parentGroup );
}

QString pSearchForm::parseGroup(QSharedPointer< const pFilterGroup > g, const QString& tableName) {
    Q_UNUSED( g );
    Q_UNUSED( tableName );
    return QString();
}

QString pSearchForm::parseFilter(QSharedPointer< const pFilter > f, const QString& tableName) {
    Q_UNUSED( f );
    Q_UNUSED( tableName );
    return QString();
}

QSharedPointer< pFilterGroup > pSearchForm::currentGroup() {
    return nullptr;
}

QSharedPointer< pFilterGroup > pSearchForm::getGroup( QModelIndex index ) {
    Q_UNUSED( index );
    return nullptr;
}
