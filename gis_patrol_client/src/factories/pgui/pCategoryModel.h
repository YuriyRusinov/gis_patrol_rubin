/*
 * @brief Класс, описывающий визуальную модель категорий
 * pCategoryModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QAbstractItemModel>
#include <QMap>
#include <QModelIndex>
#include <QSharedPointer>

class pParameter;
class pCategory;

class pCategoryModel : public QAbstractItemModel {
public:
    pCategoryModel( const QMap< qint64, QSharedPointer< pCategory > >& categories, QObject* parent = nullptr );
    ~pCategoryModel( );

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const override;
    int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

private:
    QMap< qint64, QSharedPointer< pCategory > > _categories;

private:
    Q_OBJECT
};
