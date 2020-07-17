/*
 * @brief Класс-виджет для параметров вида элемент справочника и родитель-потомок
 * pRefLineEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include "pAbstractParamWidget.h"

class QLabel;
class QLineEdit;
class QToolButton;

class pParamValue;

class pRefLineEdit : public pAbstractParamWidget {
public:
    pRefLineEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pRefLineEdit();

    void setup( ) override;

public slots:
    void setParamValue( QSharedPointer< pParamValue > pValue );

private slots:
    void changeRef();

signals:
    void changeRecord( QSharedPointer< pParamValue > pValue );

private:
    QLabel* _lParam;
    QLineEdit* _pLEValue;
    QToolButton* _tbParam;

private:
    Q_OBJECT
};
