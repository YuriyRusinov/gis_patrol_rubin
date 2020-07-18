/*
 * @brief Класс-виджет для даты
 * pTimeEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include "pAbstractParamWidget.h"

class QLabel;
class QTimeEdit;

class pParamValue;

class pTimeEdit : public pAbstractParamWidget {
public:
    pTimeEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pTimeEdit();

    void setup( ) override;

private slots:
    void pTimeChanged( const QTime &time );

private:
    QLabel* _lParam;
    QTimeEdit* _pTE;

private:
    Q_OBJECT
};
