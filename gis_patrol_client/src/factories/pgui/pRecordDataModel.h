/* 
 * @brief Класс описывает визуальную модель отображения данных
 * pRecordDataModel.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QAbstractItemModel>
#include <QList>
#include <QSharedPointer>

class pRecordCopy;
class pCategory;
class pCatParameter;

class pRecordDataModel : public QAbstractItemModel {
public:
    pRecordDataModel( QSharedPointer< pCategory > pCategory, const QMap< qint64, QSharedPointer< pRecordCopy > >& records, QObject* parent = nullptr );
    ~pRecordDataModel();

    int columnCount (const QModelIndex& parent = QModelIndex()) const override;
    int rowCount (const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex index (int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent (const QModelIndex& index) const override;
    
    Qt::ItemFlags flags (const QModelIndex& index) const override;

    QVariant data (const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData (const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool insertRows (int row, int count, const QModelIndex& parent = QModelIndex() ) override;
    bool removeRows (int row, int count, const QModelIndex& parent = QModelIndex() ) override;

private:
    void setupCategoryData();

private:
    QSharedPointer< pCategory > _pCategory;
    QMap< qint64, QSharedPointer< pRecordCopy > > _records;
    QMap< int, QSharedPointer< pCatParameter > > sortedParams;

private:
    Q_OBJECT
};
