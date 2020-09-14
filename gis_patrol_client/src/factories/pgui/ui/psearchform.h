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
#include <QMap>
#include <QSharedPointer>

class QAction;

namespace Ui {
    class p_search_form;
}

class pCategory;
class pParameter;

class pSearchForm : public QDialog {
public:
    pSearchForm( QSharedPointer< pCategory > pSearchCategory,
                 const QString& tableName,
                 const QMap<qint64, QSharedPointer< pParameter > >& pParams = QMap<qint64, QSharedPointer< pParameter > >(),
                 QWidget* parent = nullptr,
                 Qt::WindowFlags flags = Qt::WindowFlags() );
    ~pSearchForm( );

private slots:
    void saveSQLAccept( );

private:
    Ui::p_search_form* _UI;
    QAction * _delSearchEntity;

private:
    Q_OBJECT
};
