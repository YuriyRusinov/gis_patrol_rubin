/*
 * @brief Класс описывает группу поисковых фильтров по таблице или набору таблиц
 * pFilterGroup.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once			/*  */

#include <QSharedPointer>
#include <QList>

#include "pRecord.h"
class pFilter;

class pFilterGroup : public pRecord {
public:
    pFilterGroup( bool andVal = true );
    pFilterGroup( const pFilterGroup& other );
    ~pFilterGroup( );
    pFilterGroup& operator=( const pFilterGroup& other );

    void setAND( bool val=true );
    bool isAND() const;

    void addFilter( QSharedPointer< const pFilter > f );
    void addFilters( const QList< QSharedPointer< const pFilter > >& filters );
    void setFilters( const QList< QSharedPointer< const pFilter > >& filters );
    void removeFilter( int index );
    void removeFilters( int paramId );

    void addGroup( QSharedPointer< const pFilterGroup > group );
    void addGroups( const QList< QSharedPointer< const pFilterGroup > >& groups );
    void setGroups( const QList< QSharedPointer< const pFilterGroup > >& groups );
    void removeGroup( int index );

    void clear( );
    void clearFilters( );
    void clearGroups( );

    QSharedPointer< const pFilter > getFilter( int index ) const;
    const QList< QSharedPointer< const pFilter > >& getFilters( ) const;

    QSharedPointer< const pFilterGroup > getGroup( int index ) const;
    const QList< QSharedPointer< const pFilterGroup > >& getGroups( ) const;
private:
    bool _and;

    QList< QSharedPointer< const pFilterGroup > > _groups;
    QList< QSharedPointer< const pFilter > > _filters;
};

Q_DECLARE_METATYPE( pFilterGroup );
Q_DECLARE_METATYPE( QSharedPointer< pFilterGroup > );
