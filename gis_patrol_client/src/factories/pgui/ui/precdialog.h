/*
 * @brief Класс-виджет для визуального отображения записей справочников
 * precdialog.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QDialog>

class QAbstractItemModel;

namespace Ui {
    class p_rec_dialog;
}

class pRecDialog : public QDialog {
public:
    pRecDialog( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pRecDialog();

    void setRecModel( QAbstractItemModel* recModel );
    qint64 getRecId() const;

private:
    Ui::p_rec_dialog* _UI;

private:
    Q_OBJECT
};
