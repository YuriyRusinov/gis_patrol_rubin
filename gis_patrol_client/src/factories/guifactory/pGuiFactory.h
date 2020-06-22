/*
 * @brief Класс-фабрика, управляющий визуальным отображением записей
 * pGuiFactory.h
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

class PGUIFactory : public QObject {
public:
    //
    // Пока заглушка для отладки механизмов отображения и редактирования
    //
    QWidget* GUIView(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    //
    // Метод выводит виджет со списком возможных параметров в модальном mode=true или немодальном режиме
    //
    QWidget* GUIViewParams(bool mode = false, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

private slots:
    void addGroupOfParams(QAbstractItemModel* paramsModel, qint64 idParent, QModelIndex pIndex);
    void editGroupOfParams(QAbstractItemModel* paramsModel, qint64 idGroup, QModelIndex wIndex);
    void delGroupOfParams(QAbstractItemModel* paramsModel, QModelIndex wIndex);

    void addParameter( QAbstractItemModel* paramsModel, qint64 idParentGroup, QModelIndex pIndex );
    void editParameter( QAbstractItemModel* paramsModel, qint64 idParameter, QModelIndex wIndex );
    void deleteParameter( QAbstractItemModel* paramsModel, QModelIndex wIndex );

    void refreshParams();

signals:
    void viewWidget(QWidget* w);

private:
    PGUIFactory(pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent = nullptr );
    ~PGUIFactory ();

    friend class PatrolSingleton;

    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;
private:
    Q_OBJECT
};
