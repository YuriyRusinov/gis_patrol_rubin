/*
 * @brief Виджет редактирования записей
 * pCIOEditor.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QSharedPointer>
#include <QWidget>

class QAbstractItemModel;
class QAbstractItemView;
class QLineEdit;
class QModelIndex;
class QTabWidget;
class QToolBar;

class pCategory;
class pRecord;
class pRecordCopy;
class pIObject;
class pParamValue;

class pCIOEditor : public QWidget {
public:
    pCIOEditor( QSharedPointer< pCategory > pCategory,
                QSharedPointer< pRecordCopy > pRec,
                QSharedPointer< pIObject > pIO,
                bool isIO = false,
                QWidget* parent = nullptr,
                Qt::WindowFlags flags = Qt::WindowFlags()
            );
    ~pCIOEditor();

    QSharedPointer< const pCategory > getCategory() const;
    void setCategory( QSharedPointer< pCategory > pc );
    QSharedPointer< const pRecordCopy > getRecord() const;
    void setRecord ( QSharedPointer< pRecordCopy > pr );
    QSharedPointer< const pIObject > getObject() const;
    void setObject( QSharedPointer< pIObject > pIO );

    void appendTabWidget( QWidget* w, QString title );
    int getTabCount() const;
    void setCurrentPage( int num );

private slots:
    void refreshRecords( QAbstractItemView* recView );
    void searchDbRecords( QAbstractItemView* recView );
    void createNewRecord( QAbstractItemModel* recModel );
    void editSelRecord( QAbstractItemModel* recMod, const QModelIndex& recIndex );
    void delSelRecord( QAbstractItemModel* recMod, const QModelIndex& recIndex );

    void slotParamRecChanged( QSharedPointer< pParamValue > pValue );
    void slotParamIORecChanged( QSharedPointer< pParamValue > pValue );

    void slotSaveRecord();
    void slotChangeReference( QSharedPointer< pParamValue > pValue, QLineEdit* lE );

signals:
    void loadReferenceRecords( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pParamValue > pValue, QString tableName, QString columnName, QLineEdit* lE );
    void saveRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO );
    void saveRecordIO( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO );
    void createRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel );
    void openRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex );
    void delRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex );
    void refreshRecordModel( QSharedPointer< pCategory > pCat, QSharedPointer< pIObject > pRefIO, QAbstractItemView* recView );

private:
    //
    // Functions
    //
    void initActions();

private:
    //
    // Variables
    //
    friend class pIOGuiFactory;

    QSharedPointer< pCategory > _pCategory;
    QSharedPointer< pRecordCopy > _pRecord;
    QSharedPointer< pIObject > _pIO;
    bool _isIO;

    QToolBar* _tbIOActions;
    QTabWidget* _tabW;

    bool _isChanged;

private:
    Q_OBJECT
};
