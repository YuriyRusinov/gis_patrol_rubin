/*
 * @brief Класс-виджет для логических параметров
 * pCheckBox.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QCheckBox>
#include <QSharedPointer>

#include "pAbstractParamWidget.h"

class pParamValue;

class pCheckBox : public QCheckBox, public pAbstractParamWidget {
public:
    pCheckBox( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr );
    virtual ~pCheckBox();

    void setup( ) override;

private slots:
    void pStateChanged( int state );

signals:
    void valueChanged( QSharedPointer< pParamValue > pValue );

private:
    Q_OBJECT
};
