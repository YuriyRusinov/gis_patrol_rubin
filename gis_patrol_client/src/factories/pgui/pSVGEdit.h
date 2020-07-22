/*
 * @brief Класс-виджет для параметров вида SVG
 * pSVGEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include "pAbstractParamWidget.h"

class QLabel;
class QSvgWidget;
class QToolButton;

class pParamValue;

class pSVGEdit : public pAbstractParamWidget {
public:
    pSVGEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pSVGEdit();

    void setReadOnly( bool value ) override;

private slots:
    void openFile( );

private:
    void setup( ) override;

private:
    //
    // Variables
    //
    QLabel* _lParam;
    QSvgWidget* _svgWidget;
    QToolButton* _tbLoad;
};
