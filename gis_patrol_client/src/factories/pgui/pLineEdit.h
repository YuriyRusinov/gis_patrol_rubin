/*
 * @brief Класс-виджет для численных и строковых параметров
 * pLineEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include "pAbstractParamWidget.h"

class QLabel;
class QLineEdit;
class QValidator;

class pParamValue;

class pLineEdit : public pAbstractParamWidget {
public:
    pLineEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pLineEdit();

private:
    void setup( ) override;

public:
    void setReadOnly( bool value ) override;

    void setValidator( QValidator* val );

private slots:
    void pTextChanged(const QString& text);

private:
    QLabel* _lParam;
    QLineEdit* _pLE;

private:
    Q_OBJECT
};
