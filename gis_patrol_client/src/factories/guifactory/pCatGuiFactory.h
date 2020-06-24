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

class pCategory;

class pCatGuiFactory : public QObject {
public:
    QWidget* GUICatView( QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );

private slots:
    void addPCategory( QAbstractItemModel* catMod );
    void editPCategory( QAbstractItemModel* catMod, QSharedPointer< pCategory > pCat, QModelIndex cIndex );
    void delPCategory( QAbstractItemModel* catMod, QModelIndex cIndex );
    void refreshCats();

private:
    pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter,  QObject* parent=nullptr );
    ~pCatGuiFactory();
    friend class PatrolSingleton;

    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;
private:
    Q_OBJECT
};
