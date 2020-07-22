/*
 * @brief Класс-виджет для текстового поля
 * pTextEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include "pAbstractParamWidget.h"

class QLabel;
class QTextEdit;

class pParamValue;

class pTextEdit : public pAbstractParamWidget {
public:
    pTextEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pTextEdit();

    void setup( ) override;
    void setReadOnly( bool value ) override;

private slots:
    void pTextChanged();

private:
    QLabel* _lParam;
    QTextEdit* _pTextE;

private:
    Q_OBJECT
};
