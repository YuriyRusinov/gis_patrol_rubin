/*
 * @brief Класс-фабрика, управляющий визуальным отображением категорий
 * pCatGuiFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QModelIndex>
#include <QSharedPointer>
#include <QObject>

class QAbstractItemModel;
class QWidget;

class pDBLoader;
class pDBWriter;
class pParamGUIFactory;

class pCategory;

class pCatGuiFactory : public QObject {
public:
    QWidget* GUICatView( QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    QWidget* GUICategoryEditor( QSharedPointer< pCategory > pCat, QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );

public slots:
    void createCategory( QSharedPointer< pCategory > pCat, QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );
    void addPCategory( );

private slots:
    void editPCategory( QAbstractItemModel* catMod, QSharedPointer< pCategory > pCat, QModelIndex cIndex );
    void delPCategory( QAbstractItemModel* catMod, QModelIndex cIndex );
    void refreshCats();

    void addParameterToCat( QSharedPointer< pCategory > pc, QAbstractItemModel* cAttrModel );
    void removeParameterFromCat( QSharedPointer< pCategory > pc, qint64 idParameter, QModelIndex parIndex, QAbstractItemModel* cAttrModel );
    void saveCategory( QSharedPointer< pCategory > pCategory );

signals:
    void viewCatWidget( QWidget* w );

private:
    pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, pParamGUIFactory* guif, QObject* parent=nullptr );
    ~pCatGuiFactory();
    friend class PatrolSingleton;

    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;
    mutable pParamGUIFactory* _guiFactory;
private:
    Q_OBJECT
};
