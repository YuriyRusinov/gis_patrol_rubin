/* @brief Класс виджета редактирования локальных настроек приложения
 * psettingsform.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QSettings>

#include "psettingsform.h"
#include "ui_p_settings_form.h"

pSettingsForm::pSettingsForm( QSettings* pSet, QWidget* parent, Qt::WindowFlags flags )
    : QDialog( parent, flags ),
    _UI( new Ui::p_settings_form ),
    _pSettings( pSet ) {
    _UI->setupUi( this );
}

pSettingsForm::~pSettingsForm() {
    delete _UI;
}

void pSettingsForm::saveSettings() {
}

void pSettingsForm::initForm() {
}
