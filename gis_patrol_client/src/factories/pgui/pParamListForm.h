/*
 * @brief Класс-виджет, содержащий список параметров и элементы управления им
 * pParamListForm.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QDialog>
#include <QModelIndex>

class QButtonGroup;
class QToolBar;
class QTreeView;
class QAbstractItemModel;

class ParamListForm : public QDialog {
public:
    ParamListForm(bool mode=false, QWidget* parent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());
    ~ParamListForm();

    QAbstractItemModel* getParamsModel() const;
    void setParamsModel( QAbstractItemModel* paramsModel );

private slots:
    void addParamGroup();
    void editParamGroup();
    void delParamGroup();

    void addParameter();
    void editParameter();
    void delParameter();

    void refreshAll();

signals:
    void addpargroup(QAbstractItemModel* paramsModel, qint64 idParent, QModelIndex pIndex);
    void editpargroup(QAbstractItemModel* paramsModel, qint64 idGroup, QModelIndex wIndex);
    void delpargroup(QAbstractItemModel* paramsModel, QModelIndex wIndex);

    void addparam(QAbstractItemModel* paramsModel, qint64 idParentGroup, QModelIndex pIndex);
    void editparam(QAbstractItemModel* paramsModel, qint64 idParameter, QModelIndex wIndex);
    void delparam(QAbstractItemModel* paramsModel, QModelIndex wIndex);

    void refreshParams();

private:
    //
    // Functions
    //
    void init(bool mode);
    QModelIndex getGroupIndex() const;
    QModelIndex getParamIndex() const;

private:
    //
    // Variables
    //
    QToolBar* _tbParamActions;
    QTreeView* _tvParams;
    QButtonGroup* _bgParams;

private:
    Q_OBJECT
};
