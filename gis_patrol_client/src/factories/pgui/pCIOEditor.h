/*
 * @brief Виджет редактирования записей
 * pCIOEditor.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include <QSharedPointer>
#include <QWidget>

class QTabWidget;
class QToolBar;

class pCategory;
class pRecord;
class pRecordCopy;
class pIObject;

class pCIOEditor : public QWidget {
public:
    pCIOEditor( QSharedPointer< pCategory > pCategory,
                QSharedPointer< pRecordCopy > pRec,
                QSharedPointer< pIObject > pIO,
                bool isIO = false,
                QWidget* parent = nullptr,
                Qt::WindowFlags flags = Qt::WindowFlags()
            );
    ~pCIOEditor();

    QSharedPointer< const pCategory > getCategory() const;
    void setCategory( QSharedPointer< pCategory > pc );
    QSharedPointer< const pRecordCopy > getRecord() const;
    void setRecord ( QSharedPointer< pRecordCopy > pr );
    QSharedPointer< const pIObject > getObject() const;
    void setObject( QSharedPointer< pIObject > pIO );

    void appendTabWidget( QWidget* w, QString title );

private slots:
    void addRecord();
    void editRecord();
    void delRecord();

private:
    //
    // Functions
    //
    void initActions();

private:
    //
    // Variables
    //
    QSharedPointer< pCategory > _pCategory;
    QSharedPointer< pRecordCopy > _pRecord;
    QSharedPointer< pIObject > _pIO;
    bool _isIO;

    QToolBar* _tbIOActions;
    QTabWidget* _tabW;

private:
    Q_OBJECT
};