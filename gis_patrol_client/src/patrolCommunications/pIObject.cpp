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

pIObject::pIObject( )
    : _id( -1 ),
    _pCategory( nullptr ),
    _name( QString() ),
    _description( QString() ),
    _tableName( QString() ),
    _insertTime( QDateTime() ),
    _isSystem( false ),
    _isGlobal( false ),
    _recordBackground( QColor() ),
    _recordForeground( QColor() ),
    _idUser( -1 ),
    _idMaclabel( 1 ),
    _information( QString() ),
    _rIcon( QIcon() ),
    _uuid_t( QUuid() ),
    _paramValues( QList< QSharedPointer< pParamValue > >() ) {
}

pIObject::pIObject( qint64 id,
              QSharedPointer< pCategory > pCat,
              QString name,
              QString description )
    : _id( id ),
    _pCategory( pCat ),
    _name( name ),
    _description( description ),
    _tableName( QString() ),
    _insertTime( QDateTime() ),
    _isSystem( false ),
    _isGlobal( false ),
    _recordBackground( QColor() ),
    _recordForeground( QColor() ),
    _idUser( -1 ),
    _idMaclabel( 1 ),
    _information( QString() ),
    _rIcon( QIcon() ),
    _uuid_t( QUuid() ),
    _paramValues( QList< QSharedPointer< pParamValue > >() ) {
}

pIObject::pIObject( const pIObject& io )
    : _id( io._id ),
    _pCategory( io._pCategory ),
    _name( io._name ),
    _description( io._description ),
    _tableName( io._tableName ),
    _insertTime( io._insertTime ),
    _isSystem( io._isSystem ),
    _isGlobal( io._isGlobal),
    _recordBackground( io._recordBackground ),
    _recordForeground( io._recordForeground ),
    _idUser( io._idUser ),
    _idMaclabel( io._idMaclabel ),
    _information( io._information ),
    _rIcon( io._rIcon ),
    _uuid_t( io._uuid_t.toString() ),
    _paramValues( io._paramValues ) {
}

pIObject::~pIObject( ) {
    _paramValues.clear();
}

qint64 pIObject::getId() const {
    return _id;
}

void pIObject::setId( qint64 id ) {
    _id = id;
}

QSharedPointer< pCategory > pIObject::getCategory( ) const {
    return _pCategory;
}

void pIObject::setCategory( QSharedPointer< pCategory > pCat ) {
    _pCategory = pCat;
}

QString pIObject::getName( ) const {
    return _name;
}

void pIObject::setName( QString name ) {
    _name = name;
}

QString pIObject::getDesc( ) const {
    return _description;
}

void pIObject::setDesc( QString desc ) {
    _description = desc;
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

const QColor& pIObject::getBackground( ) const {
    return _recordBackground;
}

void pIObject::setBackground( const QColor& bgc ) {
    _recordBackground = bgc;
}

const QColor& pIObject::getForeground( ) const {
    return _recordForeground;
}

void pIObject::setForeground( const QColor& fgc ) {
    _recordForeground = fgc;
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

const QIcon& pIObject::getIcon( ) const {
    return _rIcon;
}

void pIObject::setIcon( const QIcon& rIcon ) {
    _rIcon = rIcon;
}

const QUuid& pIObject::uuid() const {
    return _uuid_t;
}

QUuid& pIObject::uuid() {
    return _uuid_t;
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
