/*
 * @brief Записывальщик данных в БД приложения "Защита-дозор"
 * patroldbwriter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <algorithm>
#include <defines.h>
#include <QtDebug>
#include <gis_patroldatabase.h>
#include <pParamGroup.h>
#include <pParameter.h>
#include <pParamType.h>
#include <pCategory.h>
#include <pCategoryType.h>
#include <pCatParameter.h>
#include <pParamValue.h>
#include <pIObject.h>
#include <pRecordC.h>

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
    QString sql_query = QString("select pinsertgroup( %1, %2 );").arg(pgr->getParent() ? QString::number( pgr->getParent()->getId() ) : QString("null::bigint")).arg(pgr->getName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg(pgr->getName()));
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
    QString sql_query = QString("select pUpdateGroup(%1, %2, %3);").arg( pgr->getId() ).arg(pgr->getParent() ? QString::number( pgr->getParent()->getId() ) : QString("null::bigint")).arg( pgr->getName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pgr->getName() ) );
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
    QString sql_query = QString("select pInsertParameter(%1, %2, %3, %4, %5, %6, %7);")
                            .arg( pPar->getParamType()->getId() )
                            .arg( pPar->getParamGroup()->getId() )
                            .arg( pPar->getCode().isEmpty() ? QString("null::varchar") : QString("'%1'").arg(pPar->getCode()) )
                            .arg( pPar->getName().isEmpty() ? QString("null::varchar"): QString("'%1'").arg(pPar->getName()) )
                            .arg( pPar->getTitle().isEmpty() ? QString("null::varchar") :  QString("'%1'").arg(pPar->getTitle()) )
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
    QString sql_query = QString("select pUpdateParameter(%1, %2, %3, %4, %5, %6, %7, %8);")
                            .arg( pPar->getId() )
                            .arg( pPar->getParamType()->getId() )
                            .arg( pPar->getParamGroup()->getId() )
                            .arg( pPar->getCode().isEmpty() ? QString("null::varchar") : QString("'%1'").arg(pPar->getCode()) )
                            .arg( pPar->getName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg(pPar->getName()) )
                            .arg( pPar->getTitle().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pPar->getTitle() ) )
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
    QString sql_query = QString("select cinsert( %1, %2, %3, %4, %5, %6 );")
                                .arg( pCat->getName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pCat->getName() ) )
                                .arg( pCat->getCode().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pCat->getCode() ) )
                                .arg( pCat->getDesc().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pCat->getDesc() ) )
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

    _db->begin();
    if( !pCat->getTableCat().isNull() && pCat->getTableCat()->getId() <= 0 ) {
        qint64 idChildCat = writeCategory( pCat->getTableCat() );
        if (idChildCat < 0) {
            _db->rollback();
            return -1;
        }
    }
    else if( !pCat->getTableCat().isNull() && pCat->getTableCat()->getId() > 0 ) {
        qint64 idChildCat = updateCategory( pCat->getTableCat() );
        if (idChildCat < 0) {
            _db->rollback();
            return -1;
        }
    }
    QString sql_query = QString("select cupdate( %1, %2, %3, %4, %5, %6, %7 );")
                                .arg( pCat->getId() )
                                .arg( pCat->getName().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pCat->getName() ) )
                                .arg( pCat->getCode().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pCat->getCode() ) )
                                .arg( pCat->getDesc().isEmpty() ? QString("null::varchar") : QString("'%1'").arg( pCat->getDesc() ) )
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
    QList< qint64 > oldParams = getCategoryParams( pCat->getId() );
    QList< qint64 > removeParams;
    QMap< qint64, QSharedPointer< pCatParameter > > params = pCat->categoryPars();
    /*
     * Сначала удаляем параметры, которые помечены на удаление
     */
    for (QList< qint64 >::const_iterator pop = oldParams.constBegin();
            pop != oldParams.constEnd();
            pop++ ) {
        if (!params.contains( *pop ) ) {
            qint64 res = deleteCategoryParam( pCat->getId(), *pop );
            if (res < 0) {
                _db->rollback();
                delete gpr;
                return -1;
            }
        }
    }
    for( QMap< qint64, QSharedPointer< pCatParameter > >::const_iterator pp = params.constBegin();
            pp != params.constEnd();
            pp++ ) {
        qint64 res = updateCategoryParam( pCat->getId(), pp.value() );
        if (res < 0) {
            _db->rollback();
            delete gpr;
            return -1;
        }
    }
    pCat->setId( idCat );
    delete gpr;

    _db->commit();
    return pCat->getId();
}

qint64 pDBWriter::deleteCategory( qint64 idCat ) const {
    QString sql_query = QString("select cDeleteCategory( %1 );").arg( idCat );
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

qint64 pDBWriter::insertCategoryParam( qint64 idCategory, QSharedPointer< pCatParameter> pCParam ) const {
    if( idCategory <= 0 || pCParam.isNull() )
        return -1;

    QString sql_query = QString("select cAddAttr( %1, %2, %3, %4, %5, %6 );")
                            .arg( idCategory )
                            .arg( pCParam->getId() )
                            .arg( pCParam->getDefaultValue().isNull() || pCParam->getDefaultValue().toString().isEmpty() ? QString("null::varchar") : QString("'%1'").arg (pCParam->getDefaultValue().toString()) )
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

QList< qint64 > pDBWriter::getCategoryParams( qint64 idCat ) const {
    if ( idCat <= 0 )
        return QList< qint64 >();

    QString sql_query = QString( "select * from cGetCategoryParams( %1 );").arg ( idCat );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QList< qint64 >();
    }
    int n = gpr->getRowCount();
    QList< qint64 > parList;
    for (int i=0; i<n; i++) {
        qint64 idp = gpr->getCellAsInt64( i, 0 );
        parList.append( idp );
    }
    delete gpr;
    return parList;
}

qint64 pDBWriter::deleteCategoryParam( qint64 idCat, qint64 idPar ) const {
    QString sql_query = QString( "select cDelAttr(%1, %2);").arg( idCat ).arg( idPar );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return -1;
    }
    qint64 idRes = gpr->getCellAsInt64( 0, 0 );
    delete gpr;
    return idRes;
}

qint64 pDBWriter::updateCategoryParam( qint64 idCategory, QSharedPointer< pCatParameter> pCParam ) const {
    if( idCategory <= 0 || pCParam.isNull() )
        return -1;

    QString sql_query = QString("select cUpdateAttr( %1, %2, %3, %4, %5, %6 );")
                            .arg( idCategory )
                            .arg( pCParam->getId() )
                            .arg( pCParam->getDefaultValue().isNull() ? QString("null::varchar") : QString("'%1'").arg( pCParam->getDefaultValue().toString() ) )
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

QString pDBWriter::generateUpdateRecQuery( QSharedPointer< pRecordCopy > pRecord, QString tableName ) const {
    if( pRecord.isNull() || tableName.isEmpty() )
        return QString();

    QString sql_query = QString("update %1 set ").arg( tableName );
    int n = pRecord->paramValues().count();

    for ( int i=0; i<n; i++ ) {
        QSharedPointer< const pParamValue > pVal = pRecord->paramValueIndex( i );
        QVariant val = pVal->value();
        QString valStr = pVal->valueForInsert();
        if( valStr.isEmpty() || val.isNull() || val.toString().isEmpty() )
            valStr = QString("null");
        if( QString::compare( pVal->getCatParam()->getCode(), QString("description"), Qt::CaseInsensitive ) == 0 )
            qDebug() << __PRETTY_FUNCTION__ << pVal->getCatParam()->getId() << valStr << val;
        if( pVal->getCatParam()->getId() == 1 ) // id
            continue;
        sql_query += QString(" %1=%2%3 ").arg( pVal->getCatParam()->getCode() ).arg( valStr ).arg( i==n-1 ? QString() : QString(","));
    }
    sql_query += QString(" where id = %1; ").arg( pRecord->getId() );
    return sql_query;
}

QString pDBWriter::generateInsertRecQuery( QSharedPointer< pRecordCopy > pRecord, QString tableName ) const {
    if( pRecord.isNull() || tableName.isEmpty() )
        return QString();

    qint64 id = getNextSeq( tableName );
    pRecord->setId( id );
    QString sql_query = QString("insert into %1").arg( tableName );
    QStringList columnsList;
    QStringList valuesList;
    QList< QSharedPointer< pParamValue > > pValues = pRecord->paramValues();
    int n = pValues.count();

    for ( int i = 0; i < n; i++ ) {
        columnsList << pValues[i]->getCatParam()->getCode();
        QString valStr = pValues[i]->valueForInsert();
        if( pValues[i]->getCatParam()->getId() == ATTR_IS_SYSTEM && id >= 300 )
            valStr = QString("false");
        QVariant val = pValues[i]->value();
        if( valStr.isEmpty() || val.isNull() || val.toString().isEmpty() )
            valStr = QString("null");
        valuesList << (pValues[i]->getCatParam()->getId() == ATTR_ID ? QString::number( id ) : valStr );
    }
    for ( int i = 0; i < n; i++ ) {
        sql_query += QString("%1%2%3")
                        .arg( i==0 ? QString("(") : QString() )
                        .arg( columnsList[i] )
                        .arg( i==n-1 ? QString(") values (") : QString(",") );
    }
    for ( int i = 0; i < n; i++ ) {
        sql_query += QString("%1%2")
                        .arg( valuesList[i] )
                        .arg( i==n-1 ? QString(");") : QString(",") );
    }
    return sql_query;
}

qint64 pDBWriter::getNextSeq( QString tableName, QString columnName ) const {
    QString sql_query = QString( "select getNextSeq('%1', '%2');").arg( tableName ).arg( columnName );
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

qint64 pDBWriter::insertRecord( QSharedPointer< pRecordCopy > pRecord, QSharedPointer< pIObject > pIO ) const {
    if( pIO.isNull() || pRecord.isNull() )
        return -1;
    QString tName = pIO->getTableName();
    QString sql_query = generateInsertRecQuery( pRecord, tName );
    qDebug() << __PRETTY_FUNCTION__ << sql_query;
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr ) {
        return -1;
    }

    qint64 resId = pRecord->getId();
    delete gpr;
    return resId;
}

qint64 pDBWriter::updateRecord( QSharedPointer< pRecordCopy > pRecord, QSharedPointer< pIObject > pIO ) const {
    if( pIO.isNull() || pRecord.isNull() )
        return -1;
    QString tName = pIO->getTableName();
    QString sql_query = generateUpdateRecQuery( pRecord, tName );
    qDebug() << __PRETTY_FUNCTION__ << sql_query;
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr ) {
        return -1;
    }

    qint64 resId = pRecord->getId();
    delete gpr;
    return resId;
}

qint64 pDBWriter::deleteRecord( QSharedPointer< pRecordCopy > pRecord, QSharedPointer< pIObject > pIO ) const {
    if( pIO.isNull() || pRecord.isNull() )
        return -1;

    qint64 idRec = pRecord->getId();
    QString parent_sql_query;
    QString sql_query;
    if( pIO->getId() == IO_IO_ID )
        sql_query = QString("select ioDelete( %1 );").arg( idRec );
    else {
        sql_query = QString("delete from %1 where id = %2;").arg( pIO->getTableName() ).arg( idRec );
        QSharedPointer< pCategory > pC = pIO->getCategory();
        QSharedPointer< pCategory > pCT = pC->getTableCat();
        QList< qint64 > idParents = pCT->searchParametersByType(pParamType::atParent);
        QMap< qint64, QSharedPointer< pCatParameter > > catParams = pCT->categoryPars();
        int np = idParents.size();
        for(int i=0; i<np; i++) {
            QSharedPointer< pCatParameter > pCParam = catParams.value( idParents[i] );
            parent_sql_query = QString("update %1 set %2=null where %2=%3;").arg( pIO->getTableName() ).arg( pCParam->getCode() ).arg( idRec );
            qDebug() << __PRETTY_FUNCTION__ << parent_sql_query;
            GISPatrolResult * parent_gpr = _db->execute( parent_sql_query );
            if( !parent_gpr || parent_gpr->getRowCount() != 1) {
                if( parent_gpr )
                    delete parent_gpr;
                continue;
            }
            delete parent_gpr;
        }
    }
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || ( gpr->getRowCount() != 1 && pIO->getId() == IO_IO_ID ) ) {
        if( gpr )
            delete gpr;
        return -1;
    }

    qint64 res = (pIO->getId() == IO_IO_ID ? gpr->getCellAsInt64( 0, 0 ) : idRec);
    delete gpr;
    return res;
}
