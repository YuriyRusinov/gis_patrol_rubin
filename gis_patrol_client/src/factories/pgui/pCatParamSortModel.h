/*
 * @brief Данный класс осуществляет отсортированное по порядку визуальное отображение параметров в категории
 * pPCatParamSortModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QSortFilterProxyModel>

class pCatParamSortModel : public QSortFilterProxyModel
{
public:
    pCatParamSortModel( QObject* parent = nullptr );
    /* constructor */
    ~pCatParamSortModel( );
    /* destructor */

protected:
    bool lessThan( const QModelIndex &left, const QModelIndex &right ) const override;

private:
    Q_OBJECT

}; /* -----  end of class PCatParamSortModel  ----- */
