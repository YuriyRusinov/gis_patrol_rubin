/*
 * @brief Загрузчик данных из БД приложения "Защита-дозор"
 * patroldbloader.cpp
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
#include <pCategory.h>
#include <pCategoryType.h>
#include <pCatParameter.h>

#include "patroldbloader.h"

pDBLoader::pDBLoader(GISPatrolDatabase* db, QObject* parent )
    : QObject( parent ),
    _db( db ) {
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
        qint64 idGroup = gpr->getCellAsInt64(i, 0, &ok);
        qint64 idParent = gpr->isEmpty(i, 1) ? -1 : gpr->getCellAsInt64(i, 1, &ok);
        if (!ok)
            idParent = -1;
        QString name = gpr->getCellAsString(i, 2);
        QSharedPointer< pParamGroup > parentG ( nullptr );
        QSharedPointer< pParamGroup > parg ( new pParamGroup(idGroup, name, parentG) );
        if (idParent <= 0) {
            res.insert( idGroup, parg);
        }
        else if (res.contains( idParent )) {
            parentG = res.value( idParent );
            parg->setParent( parentG );
            parentG->addChildGroup( idGroup, parg );
        }
        else {
            for(QMap< qint64, QSharedPointer< pParamGroup >>::const_iterator pg=res.constBegin();
                    pg != res.constEnd() && parentG == nullptr;
                    pg++)
                parentG = pg.value()->childGroupForId( idParent );
            if (parentG) {
                parentG->addChildGroup( idGroup, parg);
                parg->setParent( parentG );
            }
        }

        QMap< qint64, QSharedPointer< pParameter > > params = loadParameters( parg );
        parg->setParameters( params );
    }
    delete gpr;
    return res;
}

QSharedPointer< pParamGroup > pDBLoader::loadParamGroup( qint64 idGroup ) const {
    QString sql_query = QString ("select id_param_group, id_parent, name from pgetparamgroup (%1);").arg( idGroup );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return nullptr;
    }
    bool ok;
    qint64 idGroup0 = gpr->getCellAsInt64(0, 0, &ok);
    if (idGroup != idGroup0) {
        delete gpr;
        return nullptr;
    }
    qint64 idParent = gpr->isEmpty(0, 1) ? -1 : gpr->getCellAsInt64(0, 1, &ok);
    if (!ok)
        idParent = -1;
    QSharedPointer< pParamGroup > parentG = nullptr;
    if (idParent > 0)
        parentG = loadParamGroup( idParent );
    QString name = gpr->getCellAsString(0, 2);
    QSharedPointer< pParamGroup > pg ( new pParamGroup(idGroup, name, parentG) );
    if( !parentG.isNull() )
        parentG->addChildGroup( idGroup, pg );
    return pg;
}

QMap< qint64, QSharedPointer< pParameter > > pDBLoader::loadParameters( QSharedPointer< pParamGroup > pGroup) const {
    if (pGroup.isNull())
        return QMap< qint64, QSharedPointer< pParameter > >();
    qint64 idGroup = pGroup->getId();
    qDebug() << __PRETTY_FUNCTION__ << tr("Group id = %1").arg( idGroup );
    QString sql_query = QString ("select id_parameter, id_param_type, id_param_group, parameter_code, parameter_name, parameter_title, table_name, column_name, parameter_type_name, parameter_type_code from pgetparameterslist(%1)").arg( idGroup );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QMap< qint64, QSharedPointer< pParameter > >();
    }
    QMap< qint64, QSharedPointer< pParameter > > res;
    int n = gpr->getRowCount();
    int ncol = gpr->getColumnCount();
    qDebug() << __PRETTY_FUNCTION__ << n << ncol;
    QSharedPointer< pParamType > pType;
    QSharedPointer< pParameter > param;

    for( int i=0; i<n; i++) {
        qint64 idParam = gpr->getCellAsInt64(i, 0);// id
        qint64 idType = gpr->getCellAsInt64(i, 1);// id_param_type
        QString paramCode = gpr->getCellAsString(i, 3);// parameter_code
        QString paramName = gpr->getCellAsString(i, 4);// parameter_name
        QString paramTitle = gpr->getCellAsString(i, 5);// parameter_title
        QString paramTable = gpr->getCellAsString(i, 6);// table_name
        QString paramColumn = gpr->getCellAsString(i, 7);// column_name
        QString paramTypeName = gpr->getCellAsString(i, 8);// type name
        QString paramTypeCode = gpr->getCellAsString(i, 9);// type code
        pType.reset ( new pParamType( idType, paramTypeName, paramTypeCode) );
        param.reset ( new pParameter( idParam, pType, pGroup, paramCode, paramName, paramTitle, paramTable, paramColumn) );
        res.insert( idParam, param );
    }
    delete gpr;
    return res;
}

QMap< qint64, QSharedPointer< pParamType > > pDBLoader::loadAvailParamTypes() const {
    QString sql_query = QString ("select id_param_type, type_name, type_code from pGetParameterTypes();");
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QMap< qint64, QSharedPointer< pParamType > >();
    }
    QMap< qint64, QSharedPointer< pParamType > > res;
    int n = gpr->getRowCount();

    for (int i=0; i<n; i++) {
        qint64 idType = gpr->getCellAsInt64(i, 0); // id
        QString typeName = gpr->getCellAsString(i, 1); // name
        QString typeCode = gpr->getCellAsString(i, 2); // code
        QSharedPointer< pParamType > pType ( new pParamType(idType, typeName, typeCode) );
        res.insert( idType, pType );
    }
    delete gpr;
    return res;
}

QMap< qint64, QSharedPointer< pCategory > > pDBLoader::loadCategories() const {
    QString sql_query = QString("select * from cgetcategories();");
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QMap< qint64, QSharedPointer< pCategory > >();
    }
    int n = gpr->getRowCount();
    QMap< qint64, QSharedPointer< pCategory > > res;
    for (int i=0; i<n; i++) {
        qint64 idCat = gpr->getCellAsInt64(i, 0); // id
        qint64 idCatType = gpr->getCellAsInt64(i, 1); // id_type
        qint64 idChildCat = gpr->getCellAsInt64(i, 2); // id_child
        QString cName = gpr->getCellAsString(i, 3); // name
        QString cDesc = gpr->getCellAsString(i, 4); // description
        QString ctName = gpr->getCellAsString(i, 5); // type_name
        QString ctDesc = gpr->getCellAsString(i, 6); // type_desc
        bool isMain = gpr->getCellAsBool(i, 7); // is_main
        QString cCode = gpr->getCellAsString(i, 8); // code
        bool isSys = gpr->getCellAsBool(i, 9); // is_system
        bool isGlobal = gpr->getCellAsBool(i, 10);
        bool isRef = gpr->getCellAsBool( i, 11);
        Q_UNUSED( isGlobal );
        QSharedPointer< pCategoryType > pcType ( new pCategoryType( idCatType, ctName, ctDesc, isRef ) );
        QSharedPointer< pCategory > pc ( new pCategory( idCat, cName, cCode, pcType ) );
        if (idChildCat > 0) {
            QSharedPointer< pCategory > childCat = loadChildCat( idCat );
            pc->setTableCat( childCat );
        }
        pc->setMain( isMain );
        pc->setSystem( isSys );
        QMap< qint64, QSharedPointer< pCatParameter > > pcp = loadCatParameters( idCat );
        pc->setCategoryPars( pcp );
        res.insert( idCat, pc );
    }

    delete gpr;
    return res;
}

QSharedPointer< pCategory > pDBLoader::loadCategory( qint64 idCat ) const {
    QString sql_query = QString("select * from cgetcategory(%1);").arg( idCat );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return nullptr;//QMap< qint64, QSharedPointer< pCategory > >();
    }
    QMap< qint64, QSharedPointer< pCategory > > res;
    int i=0;

    qint64 idCatNew = gpr->getCellAsInt64(i, 0); // id
    Q_UNUSED( idCatNew );
    qint64 idCatType = gpr->getCellAsInt64(i, 1); // id_type
    qint64 idChildCat = gpr->getCellAsInt64(i, 2); // id_child
    QString cName = gpr->getCellAsString(i, 3); // name
    QString cDesc = gpr->getCellAsString(i, 4); // description
    QString ctName = gpr->getCellAsString(i, 5); // type_name
    QString ctDesc = gpr->getCellAsString(i, 6); // type_desc
    bool isMain = gpr->getCellAsBool(i, 7); // is_main
    QString cCode = gpr->getCellAsString(i, 8); // code
    bool isSys = gpr->getCellAsBool(i, 9); // is_system
    bool isGlobal = gpr->getCellAsBool(i, 10);
    bool isRef = false;
    Q_UNUSED( isGlobal );
    QSharedPointer< pCategoryType > pcType ( new pCategoryType( idCatType, ctName, ctDesc, isRef ) );
    QSharedPointer< pCategory > pc ( new pCategory( idCat, cName, cCode, pcType ) );
    if (idChildCat > 0) {
        QSharedPointer< pCategory > childCat = loadChildCat( idCat );
        pc->setTableCat( childCat );
    }
    pc->setMain( isMain );
    pc->setSystem( isSys );
    QMap< qint64, QSharedPointer< pCatParameter > > pcp = loadCatParameters( idCat );
    pc->setCategoryPars( pcp );

    delete gpr;
    return pc;
}

QSharedPointer< pCategory > pDBLoader::loadChildCat( qint64 idCat ) const {
    QString sql_query = QString("select * from cGetChildCategory(%1);").arg( idCat );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return nullptr;//QMap< qint64, QSharedPointer< pCategory > >();
    }
    QMap< qint64, QSharedPointer< pCategory > > res;
    int i=0;

    qint64 idChildCat = gpr->getCellAsInt64(i, 0); // id
    qint64 idCatType = gpr->getCellAsInt64(i, 1); // id_type
    qint64 idChildChildCat = gpr->getCellAsInt64(i, 2); // id_child
    QString cName = gpr->getCellAsString(i, 3); // name
    QString cDesc = gpr->getCellAsString(i, 4); // description
    QString ctName = gpr->getCellAsString(i, 5); // type_name
    QString ctDesc = gpr->getCellAsString(i, 6); // type_desc
    bool isMain = gpr->getCellAsBool(i, 7); // is_main
    QString cCode = gpr->getCellAsString(i, 8); // code
    bool isSys = gpr->getCellAsBool(i, 9); // is_system
    bool isGlobal = gpr->getCellAsBool(i, 10);
    bool isRef = false;
    Q_UNUSED( isGlobal );
    QSharedPointer< pCategoryType > pcType ( new pCategoryType( idCatType, ctName, ctDesc, isRef ) );
    QSharedPointer< pCategory > pc ( new pCategory( idChildCat, cName, cCode, pcType ) );
    if (idChildCat > 0) {
        QSharedPointer< pCategory > childCat = loadChildCat( idChildChildCat );
        pc->setTableCat( childCat );
    }
    pc->setMain( isMain );
    pc->setSystem( isSys );
    QMap< qint64, QSharedPointer< pCatParameter > > pcp = loadCatParameters( idChildCat );
    pc->setCategoryPars( pcp );

    delete gpr;
    return pc;
}

QMap< qint64, QSharedPointer< pCategoryType > > pDBLoader::loadAvailCatTypes() const {
    QString sql_query = QString("select * from cGetCategoryTypes();");
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QMap< qint64, QSharedPointer< pCategoryType > >();
    }
    QMap< qint64, QSharedPointer< pCategoryType > > res;
    int n = gpr->getRowCount();
    for (int i=0; i<n; i++) {
        qint64 idType = gpr->getCellAsInt64( i, 0 );
        QString cTypeName = gpr->getCellAsString( i, 1 );
        QString cTypeDesc = gpr->getCellAsString( i, 2 );
        QSharedPointer< pCategoryType > pCType ( new pCategoryType( idType, cTypeName, cTypeDesc ) );
        res.insert( idType, pCType );
    }
    delete gpr;
    return res;
}

QMap< qint64, QSharedPointer< pCatParameter > > pDBLoader::loadCatParameters( qint64 idCat ) const {
    QString sql_query = QString( "select * from cGetCategoryParams(%1)" ).arg( idCat );
    qDebug() << __PRETTY_FUNCTION__ << sql_query;
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() == 0 ) {
        if( gpr )
            delete gpr;
        return QMap< qint64, QSharedPointer< pCatParameter > >();
    }
    int n = gpr->getRowCount();
    QMap< qint64, QSharedPointer< pCatParameter > > res;
    for (int i=0; i<n; i++) {
        qint64 idParam = gpr->getCellAsInt64( i, 0 );
        qint64 idParamType = gpr->getCellAsInt64( i, 1 );
        QString paramCode = gpr->getCellAsString( i, 3 );// parameter_code
        QString paramName = gpr->getCellAsString( i, 4 );// parameter_name
        QString paramTitle = gpr->getCellAsString( i, 5 );// parameter_title
        QString paramTable = gpr->getCellAsString( i, 6 );// table_name
        QString paramColumn = gpr->getCellAsString( i, 7 );// column_name
        QString paramTypeName = gpr->getCellAsString( i, 8 );// type name
        QString paramTypeCode = gpr->getCellAsString( i, 9 );// type code
        QVariant paramDefVal = gpr->getCellAsString( i, 10 );// default value
        bool isMandatory = gpr->getCellAsBool( i, 11 );
        bool isReadOnly = gpr->getCellAsBool( i, 12 );
        int sort_order = gpr->getCellAsInt( i, 13 );
        qint64 id_row = gpr->getCellAsInt64( i, 14 );
        QSharedPointer< pParamType > pType ( new pParamType( idParamType, paramTypeName, paramTypeCode) );
        QSharedPointer< pParamGroup > pGroup = loadParamGroup( gpr->getCellAsInt64( i, 2) );
        QSharedPointer< pParameter > param ( new pParameter( idParam, pType, pGroup, paramCode, paramName, paramTitle, paramTable, paramColumn) );
        QSharedPointer< pCatParameter > pcParam ( new pCatParameter (*(param.data()), isMandatory, isReadOnly, paramDefVal, sort_order, id_row ) );
        res.insert( idParam, pcParam );
    }
    delete gpr;
    return res;
}

QSharedPointer< pParameter> pDBLoader::loadParameter( qint64 idParam ) const {
    QString sql_query = QString("select * from pgetparameter(%1);").arg( idParam );
    GISPatrolResult * gpr = _db->execute( sql_query );
    if( !gpr || gpr->getRowCount() != 1 ) {
        if( gpr )
            delete gpr;
        return nullptr;
    }
    int n = gpr->getRowCount();
    int ncol = gpr->getColumnCount();
    qDebug() << __PRETTY_FUNCTION__ << n << ncol;
    QSharedPointer< pParamType > pType;
    QSharedPointer< pParameter > param;

    int i=0;
    qint64 idParamNew = gpr->getCellAsInt64(i, 0);// id
    if( idParamNew != idParam ) {
        delete gpr;
        return nullptr;
    }
    qint64 idType = gpr->getCellAsInt64(i, 1);// id_param_type
    qint64 idGroup = gpr->getCellAsInt64( i, 2 );
    QSharedPointer< pParamGroup > pGroup = loadParamGroup( idGroup );
    QString paramCode = gpr->getCellAsString(i, 3);// parameter_code
    QString paramName = gpr->getCellAsString(i, 4);// parameter_name
    QString paramTitle = gpr->getCellAsString(i, 5);// parameter_title
    QString paramTable = gpr->getCellAsString(i, 6);// table_name
    QString paramColumn = gpr->getCellAsString(i, 7);// column_name
    QString paramTypeName = gpr->getCellAsString(i, 8);// type name
    QString paramTypeCode = gpr->getCellAsString(i, 9);// type code
    pType.reset ( new pParamType( idType, paramTypeName, paramTypeCode) );
    param.reset ( new pParameter( idParam, pType, pGroup, paramCode, paramName, paramTitle, paramTable, paramColumn) );
    delete gpr;
    return param;
}
