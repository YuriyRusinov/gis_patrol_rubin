/*
 * @brief Класс, описывает визуальную модель параметров категории.
 * pCatParamModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QAbstractItemModel>
#include <QList>
#include <QModelIndex>
#include <QSharedPointer>

class pCatParameter;

class pCatParametersModel : public QAbstractItemModel {
public:
    pCatParametersModel(const QMap< qint64, QSharedPointer< pCatParameter > >& paramGroups, QObject* parent = nullptr);
    ~pCatParametersModel();

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
    QMap< qint64, QSharedPointer< pCatParameter > > _pCategoryParams;
//    QList< QSharedPointer< pCatParameter > > _pCatParams;

private:
    Q_OBJECT
};
