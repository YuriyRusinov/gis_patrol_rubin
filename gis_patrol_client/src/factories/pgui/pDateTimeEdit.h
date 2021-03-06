/*
 * @brief Класс-виджет для даты-времени
 * pDateTimeEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include "pAbstractParamWidget.h"

class QLabel;
class QDateTimeEdit;

class pParamValue;

class pDateTimeEdit : public pAbstractParamWidget {
public:
    pDateTimeEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pDateTimeEdit();

    void setReadOnly( bool value ) override;

private slots:
    void pDateTimeChanged( const QDateTime &dateTime );

private:
    void setup( ) override;

    QLabel* _lParam;
    QDateTimeEdit* _pDTE;

private:
    Q_OBJECT
};
