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
#include <QObject>

class QAbstractItemModel;
class QWidget;
class pDBLoader;
class pDBWriter;

class pCatGuiFactory : public QObject {
public:
    QWidget* GUICatView( QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags() );

private:
    pCatGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter,  QObject* parent=nullptr );
    ~pCatGuiFactory();
    friend class PatrolSingleton;

    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;
private:
    Q_OBJECT
};
