/* 
 * @brief Класс для отображения параметра типа "набор элементов справочника"
 * pParamCheckWidget.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QSharedPointer>

#include "pAbstractParamWidget.h"

class QTreeView;

class pParamCheckWidget : public pAbstractParamWidget {
public:
    pParamCheckWidget( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pParamCheckWidget();

    void setReadOnly( bool value ) override;

private slots:
    void dataValueChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight );

private:
    void setup( ) override;

    QTreeView* _tvValues;

private:
    Q_OBJECT
};
