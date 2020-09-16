/*
 * @brief Класс форма поиска в таблице информационного объекта
 * psearchform.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QDialog>
#include <QList>
#include <QMap>
#include <QSharedPointer>

#include <pParamType.h>

class QAction;
class QLabel;
class QComboBox;
class QStackedLayout;
class QLineEdit;
class QCheckBox;
class QTextEdit;
class QDateEdit;
class QDateTimeEdit;
class QListView;
class QSortFilterProxyModel;
class QAbstractItemModel;
class QImage;
class QToolButton;
class QPushButton;

namespace Ui {
    class p_search_form;
}

class pCategory;
class pParameter;
class pFilterGroup;
class pFilter;

class pSearchForm : public QDialog {
public:
    pSearchForm( QSharedPointer< pCategory > pSearchCategory,
                 const QString& tableName,
                 const QMap<qint64, QSharedPointer< pParameter > >& pParams = QMap<qint64, QSharedPointer< pParameter > >(),
                 QWidget* parent = nullptr,
                 Qt::WindowFlags flags = Qt::WindowFlags() );
    ~pSearchForm( );

    QList< QSharedPointer< const pFilterGroup > >& filters();
    void setFilters( const QList< QSharedPointer< const pFilterGroup > >& filters );
private slots:
    void saveSQLAccept( );

private:
    //
    // Functions
    //
    void init();
    void initFilterTypes( pParamType::PatrolParamTypes type );
    void initAttrs();
    void initValuesWidgets (void);
    void createGroup (bool AND = true);
    void updateSQL ();

    void setFiltersModel (QAbstractItemModel * mod, const QModelIndex& parent, QSharedPointer< const pFilterGroup > parentGroup);

private:
    Ui::p_search_form* _UI;
    QAction* _delSearchEntity;
    QLabel* _lAttribute;
    QLabel* _lOper;
    QLabel* _lValue;
    QComboBox* _cbAttribute;
    QComboBox* _cbOper;

    QWidget* _wValue;
    QStackedLayout* _stLayValue;

    QLineEdit* _lEValue;
    QLineEdit* _lEStrValue;
    QCheckBox* _chCaseSensitive;
    //QComboBox * cbValue;
    QTextEdit* _teValue;
    QCheckBox* _chTextCaseSensitive;
    QCheckBox* _chValue;
    QDateEdit* _dValue;
    QDateTimeEdit* _dtValue;
    QLineEdit* _lEIntervalValue;
    QComboBox* _cbUnits;
    QListView* _lvCheckRef;
    QSortFilterProxyModel* _sortRefModel;
    QAbstractItemModel* _checkRefModel;
    QImage* _wImage;
    QToolButton* _tbImage;

    QPushButton* _pbAddFilter;

    QSharedPointer< pCategory > _pSearchCat;
    QList< QSharedPointer< const pFilterGroup > > _filters;
    QMap<qint64, QSharedPointer< pParameter > > _paramsIO;

    QMap<qint64, QSharedPointer< pParameter > > _attrsAll;

    QString _parentTable;//используется для атрибутов родитель/потомок. 
                          //Поскольку мы через атрибут не можем узнать название таблицы, 
                          //из которой делаем выборку, то это название необходимо передать в данную форму извне
private:
    //
    // Functions
    //
    QString parseGroup(QSharedPointer< const pFilterGroup > g, const QString& tableName);
    QString parseFilter(QSharedPointer< const pFilter > f, const QString& tableName);
    QSharedPointer< pFilterGroup > currentGroup();
    QSharedPointer< pFilterGroup > getGroup( QModelIndex index );

private:
    Q_OBJECT
};
