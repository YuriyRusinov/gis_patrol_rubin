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

#include <pParamType.h>

class pRecordCopy;
class pCategory;
class pCatParameter;
class pRecTreeItem;

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
    //
    // Functions
    //
    void setupParams();
    void setupCategoryData(pRecTreeItem* parent);
    QSharedPointer< const pCatParameter > getFirstParameter( pParamType::PatrolParamTypes pType );
    pRecTreeItem * getModelItem (qint64 val, pRecTreeItem * parent, QModelIndex & pIndex);
    pRecTreeItem * getItem(const QModelIndex &index) const;


private:
    pRecTreeItem* _rootItem;
    QSharedPointer< pCategory > _pCategory;
    QMap< qint64, QSharedPointer< pRecordCopy > > _records;
    QMap< int, QSharedPointer< const pCatParameter > > _sortedParams;
    QSharedPointer< const pCatParameter > _cParamParent;
    QSharedPointer< const pCatParameter > _cParamBackground;
    QSharedPointer< const pCatParameter > _cParamForeground;

private:
    Q_OBJECT
};
