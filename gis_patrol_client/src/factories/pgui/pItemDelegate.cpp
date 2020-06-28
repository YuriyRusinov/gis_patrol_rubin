/*
 * @brief Данный класс унаследован от QItemDelegate и предназначен для управления визуальным отображением
 * pItemDelegate.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pItemDelegate.h"

pItemDelegate::pItemDelegate( QObject* parent )
    : QItemDelegate( parent ) {}

pItemDelegate::~pItemDelegate() {}

QWidget* pItemDelegate::createEditor( QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const {
    return QAbstractItemDelegate::createEditor( parent, option, index );
}
