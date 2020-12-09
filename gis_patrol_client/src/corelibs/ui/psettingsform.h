/* @brief Класс виджета редактирования локальных настроек приложения
 * psettingsform.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma	once

#include <QDialog>
#include <QModelIndex>

class QAbstractItemModel;
class QSettings;

namespace Ui {
    class p_settings_form;
}

class pSettingsForm : public QDialog {
public:
    pSettingsForm( QSettings* pSet, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pSettingsForm();

private slots:
    void saveSettings();
    void settingsChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight );

private:
    //
    // Functions
    //
    void initForm();
    void setModelData( QAbstractItemModel *tModel, const QModelIndex& pIndex=QModelIndex() );
    void writeSetting( const QModelIndex& sIndex );

private:
    //
    // Variables
    //
    Ui::p_settings_form* _UI;
    QSettings* _pSettings;
    QModelIndexList _changedIndexes;

private:
    Q_OBJECT
};

