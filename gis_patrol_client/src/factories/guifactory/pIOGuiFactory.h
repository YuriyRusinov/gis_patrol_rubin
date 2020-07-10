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
 
class pIOGuiFactory : public pEntityFactory {
public:
    QWidget* GUIView( QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags() ) override;

private:
    pIOGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent = nullptr );
    pIOGuiFactory( const pIOGuiFactory& iof ) = delete;
    pIOGuiFactory& operator= ( const pIOGuiFactory& iof ) = delete;
    ~pIOGuiFactory( );

    friend class PatrolSingleton;

    mutable pDBLoader* _dbLoader;
    mutable pDBWriter* _dbWriter;

private:
    Q_OBJECT
};
