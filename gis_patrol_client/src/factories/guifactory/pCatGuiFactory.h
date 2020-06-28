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
class PGUIFactory;

class pCategory;

class pCatGuiFactory : public QObject {
public:
    QWidget* GUICatView( QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );

private slots:
    void addPCategory( QAbstractItemModel* catMod );
    void editPCategory( QAbstractItemModel* catMod, QSharedPointer< pCategory > pCat, QModelIndex cIndex );
    void delPCategory( QAbstractItemModel* catMod, QModelIndex cIndex );
    void refreshCats();

    void addParameterToCat( QSharedPointer< pCategory > pc, QAbstractItemModel* cAttrModel );
    void removeParameterFromCat( QSharedPointer< pCategory > pc, qint64 idParameter, QModelIndex parIndex, QAbstractItemModel* cAttrModel );

signals:
    void viewCatWidget( QWidget* w );

private:
    pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, PGUIFactory* guif, QObject* parent=nullptr );
    ~pCatGuiFactory();
    friend class PatrolSingleton;

    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;
    mutable PGUIFactory* _guiFactory;
private:
    Q_OBJECT
};
