/*
 * @brief Класс-виджет, содержащий список категорий и элементы управления им
 * pCategoryListForm.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QModelIndex>
#include <QWidget>

class QToolBar;
class QTreeView;
class QAbstractItemModel;

class pCategory;

class pCategoryListForm : public QWidget {
public:
    pCategoryListForm( QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    ~pCategoryListForm();

    QAbstractItemModel* getCatModel();
    void setCatModel( QAbstractItemModel* cModel );

private slots:
    void addcategory( );
    void editcategory( );
    void delcategory( );

    void refreshC( );

signals:
    void addCategory( QAbstractItemModel* mod );
    void editCategory( QAbstractItemModel* mod, QSharedPointer< pCategory > pCat, QModelIndex cIndex );
    void delCategory( QAbstractItemModel* mod, QModelIndex cIndex );

    void refrechCatMod( );

private:
    //
    // Functions
    //
    void init();
private:
    //
    // Variables
    //
    QToolBar* _tbCatActions;
    QTreeView* _tvCat;

private:
    Q_OBJECT
};
