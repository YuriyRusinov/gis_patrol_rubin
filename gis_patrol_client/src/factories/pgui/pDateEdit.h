/*
 * @brief Класс-виджет для даты
 * pDateEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include "pAbstractParamWidget.h"

class QLabel;
class QDateEdit;

class pParamValue;

class pDateEdit : public pAbstractParamWidget {
public:
    pDateEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pDateEdit();

    void setup( ) override;

private slots:
    void pDateChanged( const QDate &date );

private:
    QLabel* _lParam;
    QDateEdit* _pDE;

private:
    Q_OBJECT
};
