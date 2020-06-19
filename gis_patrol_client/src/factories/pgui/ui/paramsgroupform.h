/*
 * @brief Форма добавления/редактирования группы параметров приложения "Защита-дозор"
 * paramsgroupform.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QDialog>

namespace Ui {
    class params_group_form;
};

class ParamsGroupForm : public QDialog {
public:
    ParamsGroupForm( qint64 id=-1, QString name=QString(), QString parentName=QString(), QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    ~ParamsGroupForm();

    qint64 getId() const;

    QString getName() const;

    QString getParentName() const;

private:
    Ui::params_group_form* _UI;

private:
    Q_OBJECT
};
