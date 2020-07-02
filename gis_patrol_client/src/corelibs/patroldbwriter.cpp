/*
 * @brief Записывальщик данных в БД приложения "Защита-дозор"
 * patroldbwriter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <algorithm>
#include <QtDebug>
#include <gis_patroldatabase.h>
#include <pParamGroup.h>
#include <pParameter.h>
#include <pParamType.h>
#include <pCategory.h>
#include <pCategoryType.h>
#include <pCatParameter.h>

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
    pgr->setId( idGroup );
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

qint64 pDBWriter::insertParam( QSharedPointer< pParameter > pPar ) const {
    if (pPar.isNull())
        return -1;
    QString sql_query = QString("select pInsertParameter(%1, %2, '%3', '%4', '%5', %6, %7);")
                            .arg( pPar->getParamType()->getId() )
                            .arg( pPar->getParamGroup()->getId() )
                            .arg( pPar->getCode() )
                            .arg( pPar->getName() )
                            .arg( pPar->getTitle() )
                            .arg( pPar->getTableName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pPar->getTableName() ) )
                            .arg( pPar->getColumnName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pPar->getColumnName() ) );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idParam = gpr->getCellAsInt64(0, 0);
    pPar->setId( idParam );
    delete gpr;
    return idParam;

}

qint64 pDBWriter::updateParam( QSharedPointer< pParameter > pPar ) const {
    if (pPar.isNull())
        return -1;
    QString sql_query = QString("select pUpdateParameter(%1, %2, %3, '%4', '%5', '%6', %7, %8);")
                            .arg( pPar->getId() )
                            .arg( pPar->getParamType()->getId() )
                            .arg( pPar->getParamGroup()->getId() )
                            .arg( pPar->getCode() )
                            .arg( pPar->getName() )
                            .arg( pPar->getTitle() )
                            .arg( pPar->getTableName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pPar->getTableName() ) )
                            .arg( pPar->getColumnName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pPar->getColumnName() ) );
    qDebug() << __PRETTY_FUNCTION__ << sql_query;
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idParam = gpr->getCellAsInt64(0, 0);
    pPar->setId( idParam );
    delete gpr;
    return idParam;
}

qint64 pDBWriter::deleteParam( qint64 idParam ) const {
    if (idParam <= 0)
        return -1;
    QString sql_query = QString("select pDeleteParameter(%1);")
                            .arg( idParam );

    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idParamR = gpr->getCellAsInt64(0, 0);
    if (idParamR != idParam)
        qDebug() << __PRETTY_FUNCTION__ << idParam << idParamR;
    delete gpr;
    return idParam;
}

qint64 pDBWriter::writeCategory( QSharedPointer< pCategory > pCat ) const {
    if (_db == nullptr || pCat.isNull())
        return -1;

    _db->begin();
    if( !pCat->getTableCat().isNull() && pCat->getTableCat()->getId() <= 0 ) {
        qint64 idChildCat = writeCategory( pCat->getTableCat() );
        if (idChildCat < 0) {
            _db->rollback();
            return -1;
        }
    }
    QString sql_query = QString("select cinsert( '%1', '%2', '%3', %4, %5, %6 );")
                                .arg( pCat->getName() )
                                .arg( pCat->getCode() )
                                .arg( pCat->getDesc() )
                                .arg( pCat->getType()->getId() )
                                .arg( pCat->getTableCat().isNull() ? QString("null::int8") : QString::number( pCat->getTableCat()->getId() ) )
                                .arg( pCat->isMain() ? QString("true") : QString("false") );

    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        _db->rollback();
        return -1;
    }
    qint64 idCat = gpr->getCellAsInt64( 0, 0 );
    pCat->setId( idCat );
    delete gpr;
    QMap< qint64, QSharedPointer< pCatParameter > > pCategoryParams = pCat->categoryPars();
    QList< QSharedPointer< pCatParameter > > pCList = pCategoryParams.values();
    std::sort( pCList.begin(), pCList.end() );
    for (int i=0; i<pCList.size(); i++) {
        pCList[i]->setOrder( i+1 );
        qint64 idCPar = insertCategoryParam( idCat, pCList[i] );
        if( idCPar <= 0) {
            _db->rollback();
            return -2;
        }
    }
    _db->commit();
    return pCat->getId();
}

qint64 pDBWriter::updateCategory( QSharedPointer< pCategory > pCat ) const {
    if (pCat.isNull())
        return -1;

    return pCat->getId();
}

qint64 pDBWriter::deleteCategory( qint64 idCat ) const {
    return idCat;
}

qint64 pDBWriter::insertCategoryParam( qint64 idCategory, QSharedPointer< pCatParameter> pCParam ) const {
    if( idCategory <= 0 || pCParam.isNull() )
        return -1;

    QString sql_query = QString("select cAddAttr( %1, %2, '%3', %4, %5, %6 );")
                            .arg( idCategory )
                            .arg( pCParam->getId() )
                            .arg( pCParam->getDefaultValue().toString() )
                            .arg( pCParam->isMandatory() ? QString( "true" ) : QString( "false" ) )
                            .arg( pCParam->isReadOnly() ? QString( "true" ) : QString( "false" ) )
                            .arg( pCParam->getOrder() );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }

    qint64 res = gpr->getCellAsInt64( 0, 0 );
    delete gpr;
    return res;
}
