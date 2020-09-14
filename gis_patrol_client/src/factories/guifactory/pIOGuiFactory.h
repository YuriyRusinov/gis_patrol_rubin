/*
 * @brief Класс-фабрика для информационных объектов и записей
 * pIOGuiFactory.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma once

#include "pEntityFactory.h"

class QAbstractItemModel;
class QAbstractItemView;
class QLineEdit;

class pDBLoader;
class pDBWriter;
class pParamGUIFactory;
class pCatGuiFactory;

class pCategory;
class pRecordCopy;
class pIObject;
class pCIOEditor;
class pParamValue;
class pRecWidget;

class pIOGuiFactory : public pEntityFactory {
public:
    /*
     *--------------------------------------------------------------------------------------
     *       Class:  pIOGuiFactory
     *      Method:  QWidget :: GUIView
     * Description:  Визуальное отображение справочника информационных объектов
     *--------------------------------------------------------------------------------------
     */
    QWidget* GUIView( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) override;

    QWidget* viewRecParams( QSharedPointer< pCategory > pCategory, QSharedPointer< pRecordCopy > pRec, pCIOEditor* editor, QList< QSharedPointer< pParamValue > > paramValues = QList< QSharedPointer< pParamValue > >(), QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) const;
    QWidget* viewRecIOParams( QSharedPointer< pCategory > pCategory, QSharedPointer< pIObject > pIORec, pCIOEditor* editor, QList< QSharedPointer< pParamValue > > paramValues = QList< QSharedPointer< pParamValue > >(), QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) const;

    pCIOEditor* createRecEditor( QSharedPointer< pCategory > pCategory, QSharedPointer< pIObject > pRefIO, QSharedPointer< pRecordCopy > pRec, QList< QSharedPointer< pParamValue > > paramValues = QList< QSharedPointer< pParamValue > >(), QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) const;

    /*
     *--------------------------------------------------------------------------------------
     *       Class:  pRecWidget
     *      Method:  pRecWidget :: createRecordsWidget
     * Description:  Виджет справочника с необходимыми действиями
     *--------------------------------------------------------------------------------------
     */
    pRecWidget* createRecordsWidget( QSharedPointer< pIObject > pRefIO, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) const;

public slots:
    void createRecordCatEditor( );

private slots:
    void loadParamRef( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pParamValue > pValue, QString tableName, QString columnName, QLineEdit* lE );
    void saveRecToDb( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pIO );
    void saveIORecToDb( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pIO );
    void createNewRec( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel );
    void openRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex );
    void removeRecord( QSharedPointer< pRecordCopy > pRec, QSharedPointer< pIObject > pRefIO, QAbstractItemModel* recModel, const QModelIndex& recIndex );
    void refreshRecModel( QSharedPointer< pCategory > pCat, QSharedPointer< pIObject > pRefIO, QAbstractItemView* recView );
    void searchIORecords( QSharedPointer< pCategory > pCat, QSharedPointer< pIObject > pIO, QString tableName, QAbstractItemView* recView );

private:
    pIOGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, pParamGUIFactory* paramF, pCatGuiFactory* catF, QObject* parent = nullptr );
    pIOGuiFactory( const pIOGuiFactory& iof ) = delete;
    pIOGuiFactory& operator= ( const pIOGuiFactory& iof ) = delete;
    ~pIOGuiFactory( );

    friend class PatrolSingleton;

    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;
    mutable pParamGUIFactory* _paramFactory;
    mutable pCatGuiFactory* _catFactory;

private:
    Q_OBJECT
};
