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

class QLabel;
class QTreeView;
class QAbstractItemModel;

class pParamCheckWidget : public pAbstractParamWidget {
public:
    pParamCheckWidget( QSharedPointer< pParamValue > pValue, QAbstractItemModel* valuesModel, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    virtual ~pParamCheckWidget();

    void setReadOnly( bool value ) override;

private slots:
    void dataValueChanged( const QModelIndex& topLeft, const QModelIndex& bottomRight );

private:
    void setup( ) override;

    QLabel* _lParam;
    QTreeView* _tvValues;

private:
    Q_OBJECT
};
