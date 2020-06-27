/*
 * @brief Данный класс осуществляет отсортированное по порядку визуальное отображение параметров в категории
 * pPCatParamSortModel.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QSharedPointer>

#include <pCatParameter.h>
#include "pCatParamSortModel.h"

pCatParamSortModel::pCatParamSortModel( QObject* parent )
    : QSortFilterProxyModel( parent ) {
}

pCatParamSortModel::~pCatParamSortModel( ) {
}

bool pCatParamSortModel::lessThan( const QModelIndex& left, const QModelIndex& right ) const {
    QSharedPointer< pCatParameter > pCPLeft = left.data(Qt::UserRole+1).value< QSharedPointer< pCatParameter > >();
    QSharedPointer< pCatParameter > pCPRight = right.data(Qt::UserRole+1).value< QSharedPointer< pCatParameter > >();
    if (pCPLeft.isNull() || pCPRight.isNull())
        return QSortFilterProxyModel::lessThan( left, right );

    return *pCPLeft < *pCPRight;
}
