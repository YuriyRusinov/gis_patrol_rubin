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

class pDBLoader;
class pDBWriter;
class pParamGUIFactory;
class pCatGuiFactory;

class pCategory;
class pRecordCopy;
class pCIOEditor;
class pParamValue;
 
class pIOGuiFactory : public pEntityFactory {
public:
    QWidget* GUIView( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) override;

    QWidget* viewRecParams( QSharedPointer< pCategory > pCategory, QSharedPointer< pRecordCopy > pRec, pCIOEditor* editor, QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) const;

private slots:
    void loadParamRef( QSharedPointer< pParamValue > pValue, QString tableName, QString columnName );

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
