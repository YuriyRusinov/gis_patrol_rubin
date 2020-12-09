/* @brief Класс виджета редактирования локальных настроек приложения
 * psettingsform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QMessageBox>
#include <QSettings>
#include <QStandardItemModel>
#include <QtDebug>

#include <pSettingsDelegate.h>
#include "psettingsform.h"
#include "ui_p_settings_form.h"

const int nSettingsColumns = 2;

pSettingsForm::pSettingsForm( QSettings* pSet, QWidget* parent, Qt::WindowFlags flags )
    : QDialog( parent, flags ),
    _UI( new Ui::p_settings_form ),
    _pSettings( pSet ) {
    _UI->setupUi( this );
    initForm();

    QObject::connect( _UI->okButton, &QAbstractButton::clicked, this, &pSettingsForm::saveSettings );
    QObject::connect( _UI->tvSettings->model(), 
                      &QAbstractItemModel::dataChanged,
                      this,
                      &pSettingsForm::settingsChanged );
}

pSettingsForm::~pSettingsForm() {
    delete _UI;
}

void pSettingsForm::saveSettings() {
    for (int i=0; i<_changedIndexes.count(); i++) {
        QModelIndex ind = _changedIndexes[i];
        writeSetting( ind );
    }
    this->accept ();
}

void pSettingsForm::initForm() {
    QStringList header;
    header << QString (tr("Key")) << QString (tr("Value"));// << QString (tr("Type"));

    QStandardItemModel * tModel = new QStandardItemModel (0, nSettingsColumns);
    qDebug () << __PRETTY_FUNCTION__ << _pSettings->childGroups().count ();
    this->setModelData (tModel);
    for (int i=0; i<header.count(); i++)
        tModel->setHeaderData (i, Qt::Horizontal, header[i], Qt::DisplayRole);
    _UI->tvSettings->setModel (tModel);
    for (int column = 0; column < tModel->columnCount (QModelIndex()); ++column)
        _UI->tvSettings->resizeColumnToContents (column);
    QItemDelegate* pSetDeleg = new pSettingsDelegate;
    _UI->tvSettings->setItemDelegate( pSetDeleg );
}

void pSettingsForm::setModelData (QAbstractItemModel *tModel, const QModelIndex& pIndex) {
    if (!tModel)
        return;
    tModel->removeRows (0, tModel->rowCount (pIndex), pIndex);
    if (tModel->columnCount (pIndex) < nSettingsColumns)
        tModel->insertColumns (0, nSettingsColumns-tModel->columnCount (pIndex), pIndex);
    QStringList groups = _pSettings->childGroups();
    QStringList keys = _pSettings->childKeys();
    int nKeys = keys.count();
    tModel->insertRows (0, nKeys, pIndex);

    for (int i=0; i<nKeys; i++)
    {
        QModelIndex kIndex = tModel->index (i, 0, pIndex);
        tModel->setData (kIndex, keys[i], Qt::DisplayRole);
        QModelIndex kvIndex = tModel->index (i, 1, pIndex);
        tModel->setData (kvIndex, _pSettings->value (keys[i]), Qt::DisplayRole);
    }
    tModel->insertRows (nKeys, groups.count(), pIndex);
    for (int i=0; i<groups.count(); i++)
    {
        QModelIndex gIndex = tModel->index (nKeys+i, 0, pIndex);
        qDebug () << __PRETTY_FUNCTION__ << gIndex;
        tModel->setData (gIndex, groups[i], Qt::DisplayRole);
        _pSettings->beginGroup (groups[i]);
        this->setModelData (tModel, gIndex);
        _pSettings->endGroup ();
    }
}

void pSettingsForm::settingsChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight ) {
    qDebug () << __PRETTY_FUNCTION__ << topLeft << bottomRight;
    if( topLeft != bottomRight ) {
        QMessageBox::warning(this, tr("Settings edit"), tr("Only one settings value can be changed"), QMessageBox::Ok );
        return;
    }
    _changedIndexes.append( topLeft );
}

void pSettingsForm::writeSetting( const QModelIndex& sIndex ) {
    QStringList sGroups;
    QModelIndex keyIndex = sIndex.sibling( sIndex.row(), 0 );
    for( QModelIndex wIndex = keyIndex.parent(); wIndex.isValid(); wIndex = wIndex.parent() ) {
        sGroups.append( wIndex.data( Qt::DisplayRole ).toString() );
    }
    qDebug() << __PRETTY_FUNCTION__ << sGroups;
    int ngr = sGroups.size();
    for( int i=ngr-1; i>=0; i-- ) {
        _pSettings->beginGroup( sGroups[i] );
    }
    _pSettings->setValue( keyIndex.data( Qt::DisplayRole ).toString(), sIndex.data( Qt::DisplayRole ).toString() );
    for( int i=0; i<ngr; i++ ) {
        _pSettings->endGroup( );
    }
}
