/*
 * @brief Класс-фабрика для информационных объектов и записей
 * pIOGuiFactory.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include <QWidget>
#include <defines.h>
#include <patroldbloader.h>
#include <patroldbwriter.h>
#include <pIObject.h>
#include <pRecord.h>
#include <pRecordC.h>
#include <pCategory.h>
#include <pCIOEditor.h>

#include "pIOGuiFactory.h"

QWidget* pIOGuiFactory::GUIView( QWidget* parent, Qt::WindowFlags flags ) {
    QSharedPointer< pIObject > pIO = _dbLoader->loadIO( IO_IO_ID );
    QSharedPointer< pRecordCopy > pRec = _dbLoader->loadCopy( IO_IO_ID, pIO );
    if (pIO.isNull() || pRec.isNull() )
        return nullptr;

    QSharedPointer< pCategory > pCat = pIO->getCategory();

    QWidget* w = new pCIOEditor( pCat, pRec, pIO, false, parent, flags );
    emit viewWidget( w );
    return w;
}

pIOGuiFactory::pIOGuiFactory( pDBLoader* dbLoader, pDBWriter* dbWriter, QObject* parent )
    : pEntityFactory( parent ),
    _dbLoader( dbLoader ),
    _dbWriter( dbWriter ) {
}

pIOGuiFactory::~pIOGuiFactory( ) {}

