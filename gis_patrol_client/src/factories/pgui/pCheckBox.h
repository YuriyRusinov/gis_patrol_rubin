/*
 * @brief Класс-виджет для логических параметров
 * pCheckBox.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QSharedPointer>

#include "pAbstractParamWidget.h"

class QCheckBox;
class pParamValue;

class pCheckBox : public pAbstractParamWidget {
public:
    pCheckBox( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pCheckBox();

    void setReadOnly( bool value ) override;

private slots:
    void pStateChanged( int state );

private:
    void setup( ) override;

    QCheckBox* _pcbVal;

private:
    Q_OBJECT
};
