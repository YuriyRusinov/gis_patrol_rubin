/*
 * @brief Записывальщик данных в БД приложения "Защита-дозор"
 * patroldbwriter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <QtDebug>
#include <gis_patroldatabase.h>
#include <pParamGroup.h>
#include <pParameter.h>
#include <pParamType.h>

#include "patroldbwriter.h"

pDBWriter::pDBWriter( GISPatrolDatabase* db, QObject* parent )
    : QObject( parent ),
    _db( db ) {
}

pDBWriter::~pDBWriter() {
    _db = nullptr;
}

GISPatrolDatabase* pDBWriter::getDb() const {
    return _db;
}

void pDBWriter::setDb( GISPatrolDatabase* db ) {
    _db = db;
}

qint64 pDBWriter::writeParamGroup( QSharedPointer< pParamGroup > pgr ) const {
    if (pgr.isNull())
        return -1;
    QString sql_query = QString("select pinsertgroup( %1, '%2' );").arg(pgr->getParent() ? QString::number( pgr->getParent()->getId() ) : QString("null::bigint")).arg(pgr->getName());
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idGroup = gpr->getCellAsInt( 0, 0 );
    delete gpr;
    return idGroup;
}

qint64 pDBWriter::updateParamGroup( QSharedPointer< pParamGroup > pgr ) const {
    if (pgr.isNull())
        return -1;
    QString sql_query = QString("select pUpdateGroup(%1, %2, '%3');").arg( pgr->getId() ).arg(pgr->getParent() ? QString::number( pgr->getParent()->getId() ) : QString("null::bigint")).arg( pgr->getName() );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idGroup = gpr->getCellAsInt( 0, 0 );
    delete gpr;
    return idGroup;
}

qint64 pDBWriter::deleteParamGroup( qint64 idGroup ) const {
    if( idGroup < 0 )
        return -1;
    QString sql_query = QString("select pdeletegroup(%1);").arg( idGroup );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    delete gpr;
    return idGroup;
}
