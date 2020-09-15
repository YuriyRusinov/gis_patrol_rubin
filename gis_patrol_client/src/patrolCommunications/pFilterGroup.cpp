/*
 * @brief Класс описывает группу поисковых фильтров по таблице или набору таблиц
 * pFilterGroup.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pFilter.h"
#include "pFilterGroup.h"
#include "pParameter.h"

pFilterGroup::pFilterGroup( bool andVal )
    : pRecord( ),
    _and( andVal ),
    _groups( QList< QSharedPointer< const pFilterGroup > >() ),
    _filters( QList< QSharedPointer< const pFilter > >() ) {
}

pFilterGroup::pFilterGroup( const pFilterGroup& other )
    : pRecord( other ),
    _and( other._and ),
    _groups( other._groups ),
    _filters( other._filters ) {
}

pFilterGroup::~pFilterGroup( ) {
    _groups.clear();
    _filters.clear();
}

pFilterGroup& pFilterGroup::operator=( const pFilterGroup& other ) {
    if( &other != this ) {
        _and = other._and;
        _groups = other._groups;
        _filters = other._filters;
    }
    return *this;
}

void pFilterGroup::setAND( bool val ) {
    _and = val;
}

bool pFilterGroup::isAND() const {
    return _and;
}

void pFilterGroup::addFilter( QSharedPointer< const pFilter > f ) {
    if( f.isNull() )
        return;

    _filters.append( f );
}

void pFilterGroup::addFilters( const QList< QSharedPointer< const pFilter > >& filters ) {
    _filters.append( filters );
}

void pFilterGroup::setFilters( const QList< QSharedPointer< const pFilter > >& filters ) {
    _filters = filters;
}

void pFilterGroup::removeFilter( int index ) {
    int cnt = _filters.count();
    if( index < 0 || index >= cnt )
        return;
    _filters.removeAt( index );
}

void pFilterGroup::removeFilters( int paramId ) {
    for( int i=0; i<_filters.count(); ) {
        QSharedPointer< const pFilter > f = _filters[i];
        QSharedPointer< const pParameter > param = f->getParameter();
        if( param->getId() == paramId )
            _filters.removeAt( i );
        else
            i++;
    }
}

void pFilterGroup::addGroup( QSharedPointer< const pFilterGroup > group ) {
    if( group.isNull() )
        return;

    _groups.append( group );
}

void pFilterGroup::addGroups( const QList< QSharedPointer< const pFilterGroup > >& groups ) {
    _groups.append( groups );
}

void pFilterGroup::setGroups( const QList< QSharedPointer< const pFilterGroup > >& groups ) {
    _groups = groups;
}

void pFilterGroup::removeGroup( int index ) {
    int cnt = _groups.count();
    if( index < 0 || index >= cnt )
        return;

    _groups.removeAt( index );
}

void pFilterGroup::clear( ) {
    clearFilters();
    clearGroups();
}

void pFilterGroup::clearFilters( ) {
    _filters.clear();
}

void pFilterGroup::clearGroups( ) {
    _groups.clear();
}

QSharedPointer< const pFilter > pFilterGroup::getFilter( int index ) const {
    int cnt = _filters.count();
    if( index < 0 || index >= cnt )
        return nullptr;

    return _filters.at( index );
}

const QList< QSharedPointer< const pFilter > >& pFilterGroup::getFilters( ) const {
    return _filters;
}

QSharedPointer< const pFilterGroup > pFilterGroup::getGroup( int index ) const {
    int cnt = _groups.count();
    if( index < 0 || index >= cnt )
        return nullptr;

    return _groups.at( index );
}

const QList< QSharedPointer< const pFilterGroup > >& pFilterGroup::getGroups( ) const {
    return _groups;
}
