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
#include <QSharedPointer>

#include "pEntityFactory.h"

class QAbstractItemModel;
class QWidget;
class pDBLoader;
class pDBWriter;
class pParamGroup;
class pCatParameter;
class pParamValue;
class pAbstractParamWidget;

class pParamGUIFactory : public pEntityFactory {
public:
    //
    // Формирование и вывод в немодальном режиме древовидной структуры параметров и групп параметров
    //
    QWidget* GUIView(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags()) override;
    //
    // Метод выводит виджет со списком возможных параметров в модальном mode=true или немодальном режиме
    //
    QWidget* GUIViewParams(bool mode = false, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    //
    // Метод формирует для редактирования значения параметра специальный
    // виджет для его дальнейшего размещения на форме
    //
    pAbstractParamWidget* createParamWidget( QSharedPointer< pParamValue > pCParamValue, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

private slots:
    void addGroupOfParams(QAbstractItemModel* paramsModel, qint64 idParent, QModelIndex pIndex);
    void editGroupOfParams(QAbstractItemModel* paramsModel, qint64 idGroup, QModelIndex wIndex);
    void delGroupOfParams(QAbstractItemModel* paramsModel, QModelIndex wIndex);

    void addParameter( QAbstractItemModel* paramsModel, qint64 idParentGroup, QModelIndex pIndex );
    void editParameter( QAbstractItemModel* paramsModel, qint64 idParameter, QModelIndex wIndex );
    void deleteParameter( QAbstractItemModel* paramsModel, QModelIndex wIndex );

    void refreshParams();

private:
    //
    // Functions
    //
    pParamGUIFactory(pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent = nullptr );
    ~pParamGUIFactory ();
    void buildParamModel( QAbstractItemModel* pModel, const QMap< qint64, QSharedPointer< pParamGroup >>& pGroups, QModelIndex parent=QModelIndex()) const;

    friend class PatrolSingleton;

    //
    // Variables
    //
    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;
private:
    Q_OBJECT
};
