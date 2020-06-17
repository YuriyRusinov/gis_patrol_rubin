/*
 * @brief Загрузчик данных из БД приложения "Защита-дозор"
 * patroldbloader.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */
#include <gis_patroldatabase.h>
#include <pParamGroup.h>
#include <pParameter.h>
#include <pParamType.h>

#include "patroldbloader.h"

pDBLoader::pDBLoader( QObject* parent )
    : QObject( parent ),
    _db( nullptr ) {
}

pDBLoader::~pDBLoader() {
    _db = nullptr;
}

GISPatrolDatabase* pDBLoader::getDb() const {
    return _db;
}

void pDBLoader::setDb( GISPatrolDatabase* db ) {
    _db = db;
}

QMap< qint64, QSharedPointer< pParamGroup > > pDBLoader::loadGroupedParameters() const {
    QString sql_query ("select id_param_group, id_parent, name from pgetparamgroups (null);");
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QMap< qint64, QSharedPointer< pParamGroup > >();
    }
    
    QMap< qint64, QSharedPointer< pParamGroup > > res;
    int n = gpr->getRowCount();
    for( int i=0; i<n; i++) {
        bool ok;
        qint64 idGroup = gpr->getCellAsInt(i, 0, &ok);
        qint64 idParent = gpr->isEmpty(i, 1) ? -1 : gpr->getCellAsInt(i, 1, &ok);
        if (!ok)
            idParent = -1;
        QString name = gpr->getCellAsString(i, 2);
        pParamGroup* parentG = nullptr;
        //
        // Запрос в БД построен так, что родительские группы идут перед дочерними,
        // поэтому родительская группа окажется в результате на момент анализа результата
        // запроса к БД
        //
        if (idParent > 0) {
            QMap< qint64, QSharedPointer< pParamGroup > >::const_iterator pp = res.constFind( idParent );
            if (pp == res.constEnd())
                parentG = loadParamGroup( idParent );
            else {
                QSharedPointer< pParamGroup > ppg = pp.value();
                parentG = ppg.get();
            }
        }

        QSharedPointer< pParamGroup > pg ( new pParamGroup(idGroup, name, parentG) );
        QMap< qint64, QSharedPointer< pParameter > > params = loadParameters( pg.get() );
        pg->setParameters( params );
        res.insert( idGroup, pg );
    }
    delete gpr;
    return res;
}

pParamGroup* pDBLoader::loadParamGroup( int idGroup ) const {
    QString sql_query = QString ("select id_param_group, id_parent, name from pgetparamgroup (%1);").arg( idGroup );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return nullptr;
    }
    bool ok;
    qint64 idGroup0 = gpr->getCellAsInt(0, 0, &ok);
    if (idGroup != idGroup0) {
        delete gpr;
        return nullptr;
    }
    qint64 idParent = gpr->isEmpty(0, 1) ? -1 : gpr->getCellAsInt(0, 1, &ok);
    if (!ok)
        idParent = -1;
    pParamGroup* parentG = nullptr;
    if (idParent > 0)
        parentG = loadParamGroup( idParent );
    QString name = gpr->getCellAsString(0, 2);
    pParamGroup* pg ( new pParamGroup(idGroup, name, parentG) );
    if( parentG )
        parentG->addChildGroup( pg );
    return pg;
}

QMap< qint64, QSharedPointer< pParameter > > pDBLoader::loadParameters( pParamGroup* pGroup ) const {
    qint64 idGroup = pGroup->getId();
    QString sql_query = QString ("select id_parameter, id_param_type, id_param_group, parameter_code, parameter_name, parameter_title, table_name, column_name, parameter_type_name, parameter_type_code from pgetparameterslist(%1)").arg( idGroup );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QMap< qint64, QSharedPointer< pParameter > >();
    }
    QMap< qint64, QSharedPointer< pParameter > > res;
    int n = gpr->getRowCount();
    for( int i=0; i<n; i++) {
        qint64 idParam = gpr->getCellAsInt(i, 0);// id
        qint64 idType = gpr->getCellAsInt(i, 1);// id_param_type
        QString paramCode = gpr->getCellAsString(i, 2);// parameter_code
        QString paramName = gpr->getCellAsString(i, 3);// parameter_name
        QString paramTitle = gpr->getCellAsString(i, 4);// parameter_title
        QString paramTable = gpr->getCellAsString(i, 5);// table_name
        QString paramColumn = gpr->getCellAsString(i, 6);// column_name
        QString paramTypeName = gpr->getCellAsString(i, 7);// type name
        QString paramTypeCode = gpr->getCellAsString(i, 8);// type code
        pParamType* pType = new pParamType( idType, paramTypeName, paramTypeCode);
        pParameter* param = new pParameter( idParam, pType, pGroup, paramCode, paramName, paramTitle, paramTable, paramColumn);
        res.insert( idParam, QSharedPointer< pParameter >(param) );
    }
    delete gpr;
    return res;
}
