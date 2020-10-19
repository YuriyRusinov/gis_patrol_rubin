/*
 * @brief Класс-виджет для параметров геометрического типа
 * pGeomForm.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QSharedPointer>

#include "pAbstractParamWidget.h"

class QComboBox;
class QLabel;
class QTableView;
class QToolButton;

class pParamValue;

class pGeomForm : public pAbstractParamWidget {
public:
    pGeomForm( QSharedPointer< pParamValue > pValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    ~pGeomForm();

    void setReadOnly( bool value ) override;

private:
    void setup( ) override;

private slots:
    void geomTypeChanged();
    void addPoint();
    void removePoint();

private:
    QLabel* _lParam;
    QComboBox* _cbGeomType;
    QTableView* _tvPoints;
    QToolButton* _tbAddPoint;
    QToolButton* _tbRemovePoint;

private:
    Q_OBJECT
};
