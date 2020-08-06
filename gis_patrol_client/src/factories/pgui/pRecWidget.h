/*
 * @brief Класс-виджет для отображения записей справочника и соответствующих операций
 * pRecWidget.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QWidget>

class QAbstractItemModel;
class QAbstractItemView;
class QAction;
class QModelIndex;
class QToolBar;
class QTreeView;

class pRecWidget : public QWidget {
public:
    /* ====================  LIFECYCLE     ======================================= */
    pRecWidget( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() );
    /* constructor */
    virtual ~pRecWidget();

    /* ====================  ACCESSORS     ======================================= */
    QAbstractItemModel* getSourceModel() const;
    qint64 getRecId() const;

    /* ====================  MUTATORS      ======================================= */
    void setSourceModel( QAbstractItemModel* recModel );

    /* ====================  OPERATORS     ======================================= */

public slots:
    void refreshModel();

private slots:
    void addNewRecord();
    void editSelectedRecord();
    void delSelectedRecord();

signals:
    void refreshRecords( QAbstractItemView* recView );
    void addRecord( QAbstractItemModel* recMod );
    void editRecord( QAbstractItemModel* recMod, const QModelIndex& wIndex );
    void delRecord( QAbstractItemModel* recMod, const QModelIndex& wIndex );

private:
    /* ====================  METHODS       ======================================= */
    void setup( );

    friend class pIOGuiFactory;
    /* ====================  DATA MEMBERS  ======================================= */
    QToolBar* _tbRecActions;
    QTreeView* _tvRecords;

private:
    Q_OBJECT
}; /* -----  end of class PRecWidget  ----- */

