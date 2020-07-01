/*
 * @brief Данный класс унаследован от QWidget и предназначен для визуализации и редактирования категории
 * pCatEditor.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QMap>
#include <QModelIndex>
#include <QWidget>
#include <QSharedPointer>

class QAbstractItemModel;
class QComboBox;
class QLabel;
class QLineEdit;
class QSortFilterProxyModel;
class QTabWidget;
class QToolBar;
class QTreeView;

class pCategory;
class pCategoryType;

class pCatEditor : public QWidget {
public:
    pCatEditor( QSharedPointer< pCategory > pCat = nullptr, const QMap< qint64, QSharedPointer< pCategoryType >>& pAvailCatTypes = QMap< qint64, QSharedPointer< pCategoryType >>(), QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    ~pCatEditor( );

    QSharedPointer< pCategory > getCategory() const;
    void setCategory( QSharedPointer< pCategory > pc );

    void setCatParamModel( QAbstractItemModel* paramModel );
    void setTableCatParamModel( QAbstractItemModel* paramModel );

public slots:
    void saveCategory( );

private slots:
    void addParamIntoCat();
    void removeParamFromCat();
    void addParamIntoTableCat();
    void removeParamFromTableCat();

    void upParamInCat();
    void downParamInCat();
    void upParamInTableCat();
    void downParamInTableCat();

    void cTypeIndexChanged( int index );

signals:
    void addParameterIntoCategory( QSharedPointer< pCategory > pc, QAbstractItemModel* cAttrModel );
    void removeParameterFromCategory( QSharedPointer< pCategory > pc, qint64 idParameter, QModelIndex parIndex, QAbstractItemModel* cAttrModel );
    void saveCat( QSharedPointer< pCategory > pc);

private:
    //
    // Functions
    //
    void init( );
    void initActions( );
    void initCatParams( );
    void initTableCatParams( );
    void initValues( );

private:
    //
    // Variables
    //
    QSharedPointer< pCategory > _pCategory;
    QMap< qint64, QSharedPointer< pCategoryType > > _availCatTypes;

    QToolBar* _tbCatActions;
    QTabWidget* _tabCatWidget;

    QWidget* _catParamWidget;
    QLabel* _lCatName;
    QLineEdit* _lECatName;
    QLabel* _lCatCode;
    QLineEdit* _lECatCode;
    QLabel* _lCatDesc;
    QLineEdit* _lECatDesc;
    QLabel* _lCatType;
    QComboBox* _cbCatTypes;
    QWidget* _wCatParams;
    QToolBar* _tbCatParamsActions;
    QTreeView* _tvCatParams;

    QWidget* _tableCatParamWidget;
    QLabel* _lTableCatName;
    QLineEdit* _lETableCatName;
    QLabel* _lTableCatCode;
    QLineEdit* _lETableCatCode;
    QLabel* _lTableCatDesc;
    QLineEdit* _lETableCatDesc;
    QWidget* _wTableCatParams;
    QToolBar* _tbTableCatParamsActions;
    QTreeView* _tvTableCatParams;

    QSortFilterProxyModel* _cSortModel;
    QSortFilterProxyModel* _cTSortModel;
private:
    Q_OBJECT
};
