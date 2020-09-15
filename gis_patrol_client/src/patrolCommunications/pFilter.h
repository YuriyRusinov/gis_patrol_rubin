/*
 * @brief Класс описывает поисковый фильтр по таблице или набору таблиц
 * pFilter.h
 *
 * Comment: фильтр по атрибуту
 *    используется при фильтрации справочников, табелей, журналов и прочих  ИО, которые являются контейнерными.
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QList>
#include <QSharedPointer>

#include "pRecord.h"

class pParameter;
class pParamValue;

class pFilter : public pRecord {
public:
    enum FilterOper{
        foEq = 1, // =
        foGr = 2, // >
        foLess = 3, // <
        foGrEq = 4, // >=
        foLessEq = 5, // <=
        foIn = 6, // in ()
        foNotIn = 7, // not in ()
        /**/foBetween = 8, // between %1 and %2
        foLike = 9, // like 'AAA'
        foNotEq = 10, // <>
        foIsNull = 11, //isnull
        foIsNotNull = 12, //is not null
        /**/foInSQL = 13, // in (select ...)
        foLikeIn = 14, //LIKE '%AAA%'
        foLikeStart = 15, //LIKE 'AAA%'
        foLikeEnd = 16, //LIKE '%AAA'
    };
    pFilter( );
    pFilter( QSharedPointer< const pParameter > param, QSharedPointer< const pParamValue > pvalue, pFilter::FilterOper oper );
    pFilter( const pFilter& otherFilter );
    ~pFilter( );

    QSharedPointer< const pParameter > getParameter( ) const;
    void setParameter( QSharedPointer< const pParameter > param );

    QSharedPointer< const pParamValue > getValue( int index ) const;
    void setValue( QSharedPointer< const pParamValue > pvalue );
    void addValue( QSharedPointer< const pParamValue > pvalue );
    void setValues( const QList< QSharedPointer< const pParamValue > >& pvalues );
    void removeValue( int index );
    void clearValues( );

    pFilter::FilterOper getOperation( ) const;
    void setOperation( pFilter::FilterOper oper );

    bool isCaseSensitive( ) const;
    void setCaseSensitive( bool val );

    bool isRecursive( ) const;
    void setRecursive( bool val );

    bool isCorrect() const;
    QString constructForIn() const;

    bool operator== (const pFilter& anotherFilter) const;
    bool operator!= (const pFilter& anotherFilter) const;

private:
    QSharedPointer< const pParameter > _parameter;
    QList< QSharedPointer< const pParamValue > > _values;
    FilterOper _oper;
    bool _caseSensitive;
    bool _recursive;
};

Q_DECLARE_METATYPE( pFilter );
Q_DECLARE_METATYPE( QSharedPointer< pFilter > );
