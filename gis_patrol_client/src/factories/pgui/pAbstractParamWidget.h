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

class pAbstractParamWidget : public QWidget {
public:
    pAbstractParamWidget( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pAbstractParamWidget();

    QSharedPointer< const pParamValue > paramValue() const;
    QSharedPointer< pParamValue > paramValue();
    void setParamValue( QSharedPointer< pParamValue > pValue );

    virtual void setReadOnly( bool value ) = 0;

private:
    virtual void setup( ) = 0;

signals:
    void valueChanged( QSharedPointer< pParamValue > pValue );

private:
    QSharedPointer< pParamValue > _paramValue;

private:
    Q_OBJECT
};
