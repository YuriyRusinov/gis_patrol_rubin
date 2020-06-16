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

    void refresh();
private:
    //
    // Functions
    //
    void init(bool mode);

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
