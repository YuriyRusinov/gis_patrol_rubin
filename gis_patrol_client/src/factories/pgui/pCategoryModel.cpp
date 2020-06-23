/*
 * @brief Класс, описывающий визуальную модель категорий
 * pCategoryModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <pCategory.h>
#include "pCategoryModel.h"

pCategoryModel::pCategoryModel( const QMap< qint64, QSharedPointer< pCategory > >& categories, QObject* parent )
    : QAbstractItemModel( parent ),
    _categories( categories ) {
}

pCategoryModel::~pCategoryModel( ) {
}

Qt::ItemFlags pCategoryModel::flags(const QModelIndex& index) const {
}

bool pCategoryModel::setData(const QModelIndex& index, const QVariant &value, int role) {
}

int pCategoryModel::columnCount( const QModelIndex& parent ) const {
}

int pCategoryModel::rowCount( const QModelIndex& parent ) const {
}

QModelIndex pCategoryModel::index(int row, int column, const QModelIndex &parent) const {
}

QModelIndex pCategoryModel::parent(const QModelIndex &index) const {
}

QVariant pCategoryModel::data(const QModelIndex &index, int role) const {
}

QVariant pCategoryModel::headerData(int section, Qt::Orientation orientation, int role) const {
}

bool pCategoryModel::insertRows(int position, int rows, const QModelIndex &parent) {
}

bool pCategoryModel::removeRows(int position, int rows, const QModelIndex &parent) {
}
