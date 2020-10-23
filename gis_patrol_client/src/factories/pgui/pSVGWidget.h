/*
 * @brief Класс-виджет для параметров вида SVG
 * pSVGWidget.h
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

class pSVGWidget : public pAbstractParamWidget {
public:
    pSVGWidget( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pSVGWidget();

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
    QByteArray _SVGContents;
};
