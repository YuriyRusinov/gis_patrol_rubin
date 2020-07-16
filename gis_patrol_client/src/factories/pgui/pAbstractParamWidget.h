/*
 * @brief Базовый класс для виджетов, работающих с параметрами записей в БД
 * pAbstractParamWidget.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QSharedPointer>
#include <QWidget>

class QLayout;

class pParamValue;

class pAbstractParamWidget {//: public QWidget {
public:
    pAbstractParamWidget( QSharedPointer< pParamValue > pValue );
    virtual ~pAbstractParamWidget();

    QSharedPointer< const pParamValue > paramValue() const;
    QSharedPointer< pParamValue > paramValue();
    void setParamValue( QSharedPointer< pParamValue > pValue );

    virtual void setup( ) = 0;

private:
    QSharedPointer< pParamValue > _paramValue;

//private:
//    Q_OBJECT
};
