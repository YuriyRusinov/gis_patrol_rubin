/* @brief Класс виджета редактирования локальных настроек приложения
 * psettingsform.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma	once

#include <QDialog>

class QSettings;

namespace Ui {
    class p_settings_form;
}

class pSettingsForm : public QDialog {
public:
    pSettingsForm( QSettings* pSet, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pSettingsForm();

public slots:
    void saveSettings();

private:
    void initForm();

private:
    Ui::p_settings_form* _UI;
    QSettings* _pSettings;

private:
    Q_OBJECT
};

