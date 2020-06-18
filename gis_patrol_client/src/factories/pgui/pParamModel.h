/*
 * @brief Класс, описывающий визуальную модель параметров, сгруппированных по подходящим пользовательским группам
 * pParamModel.h
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

class pParamGroup;
class pParameter;
class pTreeItem;

class ParametersModel : public QAbstractItemModel {
public:
    ParametersModel(const QMap< qint64, QSharedPointer< pParamGroup > >& paramGroups, QObject* parent = nullptr);
    ~ParametersModel();

    int columnCount( const QModelIndex &parent = QModelIndex() ) const override;
    int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    void setupModel(const QMap< qint64, QSharedPointer< pParamGroup > >& paramGroups, pTreeItem* rootItem );

private:
    QMap< qint64, QSharedPointer< pParamGroup > > _paramGroups;
    pTreeItem* _rootItem;

private:
    Q_OBJECT
};
