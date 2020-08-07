/* 
 * @brief Класс описывает визуальную модель отображения данных с возможностью их выбора
 * pCheckableDataModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QList>
#include <QSharedPointer>

#include "pRecordDataModel.h"

class pRecordCopy;
class pCategory;
class pCatParameter;
class pParamValue;

class pCheckableDataModel : public pRecordDataModel
{
public:
    /* ====================  LIFECYCLE     ======================================= */
    pCheckableDataModel ( QSharedPointer< pParamValue > pRefParamValue, QSharedPointer< pCategory > pCategory, const QMap< qint64, QSharedPointer< pRecordCopy > >& records, QObject* parent = nullptr );
    /* constructor */
    ~pCheckableDataModel();

    /* ====================  ACCESSORS     ======================================= */
    QVariant data (const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData (const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    /* ====================  METHODS       ======================================= */

    /* ====================  DATA MEMBERS  ======================================= */
    QSharedPointer< const pParamValue > _pReferenceParameterValue;

private:
    Q_OBJECT
}; /* -----  end of class PCheckableDataModel  ----- */

