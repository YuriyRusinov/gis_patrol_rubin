/*
 * @brief Класс виджет для цвета фона.
 * pColorEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include "pAbstractParamWidget.h"

class QLabel;
class QToolButton;

class pColorEdit : public pAbstractParamWidget {
public:
    pColorEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    ~pColorEdit();

    void setReadOnly( bool value ) override;

private:
    void setup( ) override;

private slots:
    void setColor();

private:
    //
    // Variables
    //
    QLabel* _lParam;
    QLabel* _lColorLabel;
    QToolButton* _tbColor;

private:
    Q_OBJECT
};
