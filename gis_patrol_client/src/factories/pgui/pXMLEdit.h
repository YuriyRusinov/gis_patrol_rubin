/*
 * @brief Класс виджета, работающий с xml
 * pXMLEdit.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include "pAbstractParamWidget.h"

class QLabel;
class QTextEdit;
class QToolButton;

class pParamValue;

class pXMLEdit : public pAbstractParamWidget {
public:
    pXMLEdit( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    ~pXMLEdit( );

    void setReadOnly( bool value ) override;

private:
    void setup( ) override;

private slots:
    void loadXml();

private:
    QLabel* _lParam;
    QTextEdit* _xmlTE;
    QToolButton* _tbXml;

private:
    Q_OBJECT
};
