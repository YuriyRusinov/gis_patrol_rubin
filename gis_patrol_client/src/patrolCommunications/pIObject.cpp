/*
 * @brief Класс описывает информационный объект, являющийся справочником или документом
 * pIObject.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pCatParameter.h"
#include "pParamValue.h"
#include "pIObject.h"

pIObject::pIObject( ) : pRecord( ),
    _pCategory( nullptr ),
    _tableName( QString() ),
    _insertTime( QDateTime() ),
    _isSystem( false ),
    _isGlobal( false ),
    _idUser( -1 ),
    _idMaclabel( 1 ),
    _information( QString() ),
    _paramValues( QList< QSharedPointer< pParamValue > >() ) {
}

pIObject::pIObject( qint64 id,
              QSharedPointer< pCategory > pCat,
              QString name,
              QString description )
    : pRecord( id, name, description ),
    _pCategory( pCat ),
    _tableName( QString() ),
    _insertTime( QDateTime() ),
    _isSystem( false ),
    _isGlobal( false ),
    _idUser( -1 ),
    _idMaclabel( 1 ),
    _information( QString() ),
    _paramValues( QList< QSharedPointer< pParamValue > >() ) {
}

pIObject::pIObject( const pIObject& io )
    : pRecord( io),
    _pCategory( io._pCategory ),
    _tableName( io._tableName ),
    _insertTime( io._insertTime ),
    _isSystem( io._isSystem ),
    _isGlobal( io._isGlobal),
    _idUser( io._idUser ),
    _idMaclabel( io._idMaclabel ),
    _information( io._information ),
    _paramValues( io._paramValues ) {
}

pIObject::~pIObject( ) {
    _paramValues.clear();
}

QSharedPointer< pCategory > pIObject::getCategory( ) const {
    return _pCategory;
}

void pIObject::setCategory( QSharedPointer< pCategory > pCat ) {
    _pCategory = pCat;
}

QString pIObject::getTableName( ) const {
    return _tableName;
}

void pIObject::setTableName( QString tableName ) {
    _tableName = tableName;
}

const QDateTime& pIObject::insertTime( ) const {
    return _insertTime;
}

QDateTime& pIObject::insertTime( ) {
    return _insertTime;
}

void  pIObject::setInsertTime( const QDateTime& dt ) {
    _insertTime = dt;
}

bool pIObject::isSystem( ) const {
    return _isSystem;
}

void pIObject::setSystem( bool sys ) {
    _isSystem = sys;
}

bool pIObject::isGlobal( ) const {
    return _isGlobal;
}

void pIObject::setGlobal( bool global ) {
    _isGlobal = global;
}

qint64 pIObject::getAuthor( ) const {
    return _idUser;
}

void pIObject::setAuthor( qint64 idAuthor ) {
    _idUser = idAuthor;
}

int pIObject::getMacLabel( ) const {
    return _idMaclabel;
}

void pIObject::setMacLabel( int ml ) {
    _idMaclabel = ml;
}

QString pIObject::getInfo( ) const {
    return _information;
}

void pIObject::setInfo( const QString& info ) {
    _information = info;
}

const QList< QSharedPointer< pParamValue > >& pIObject::paramValues() const {
    return _paramValues;
}

QList< QSharedPointer< pParamValue > >& pIObject::paramValues() {
    return _paramValues;
}

void pIObject::setParamValues( QList< QSharedPointer< pParamValue > >& pVals ) {
    _paramValues = pVals;
}

void pIObject::addParamValue( QSharedPointer< pParamValue > pVal ) {
    if( pVal.isNull() )
        return;

    _paramValues.append( pVal );
}

qint64 pIObject::removeParamValue( qint64 _id ) {
    int count = _paramValues.size();
    int cnt = 0;
    for (int i=0; i<count; ) {
        QSharedPointer< pCatParameter > ca = _paramValues[i]->getCatParam();
        if( ca->getId() == _id ) {
            _paramValues.removeAt( i );
            cnt++;
            count--;
        }
        else
            i++;
    }
    if( cnt == 0 )
        return -1;

    return _id;
}

qint64 pIObject::removeParamValue( QSharedPointer< pParamValue > pVal ) {
    if( pVal.isNull() )
        return -1;

    int cnt = _paramValues.removeAll( pVal );
    if( cnt == 0 )
        return -1;

    return 1;
}

qint64 pIObject::removeParamValueInd( qint64 index ) {
    if( index < 0 || index >= _paramValues.size() )
        return -1;

    _paramValues.removeAt( index );

    return 1;
}
