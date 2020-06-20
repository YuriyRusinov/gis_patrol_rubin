/*
 * @brief Форма добавления/редактирования параметра приложения "Защита-дозор"
 * paramsgroupform.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#pragma once

#include <QDialog>

namespace Ui {
    class params_form;
}

class ParamsForm : public QDialog {
public:
    ParamsForm( qint64 id, const QMap<int, QString>& pTypes, QWidget* parent = nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    ~ParamsForm();

    qint64 getId() const;
    QString getName() const;
    QString getCode() const;
    QString getTitle() const;
    int getType() const;
    QString getTableName() const;
    QString getColumnName() const;

private slots:
    void cbTypeActivated(int index);

private:
    Ui::params_form* _UI;

private:
    Q_OBJECT
};
