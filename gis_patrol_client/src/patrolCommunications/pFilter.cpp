/*
 * @brief Класс описывает поисковый фильтр по таблице или набору таблиц
 * pFilter.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pParameter.h"
#include "pParamValue.h"
#include "pFilter.h"

pFilter::pFilter( ) : pRecord (),
    _parameter( nullptr ),
    _values( QList< QSharedPointer< const pParamValue > >() ),
    _oper( pFilter::foEq ),
    _caseSensitive( false ),
    _recursive( false ) {
}

pFilter::pFilter( QSharedPointer< const pParameter > param, QSharedPointer< const pParamValue > pvalue, pFilter::FilterOper oper )
    : pRecord( ),
    _parameter( param ),
    _values( QList< QSharedPointer< const pParamValue > >() ),
    _oper( oper ),
    _caseSensitive( false ),
    _recursive( false ) {
    _values.append( pvalue );
}

pFilter::pFilter( const pFilter& otherFilter ) : pRecord( otherFilter ),
    _parameter( otherFilter._parameter ),
    _values( otherFilter._values ),
    _oper( otherFilter._oper ),
    _caseSensitive( otherFilter._caseSensitive ),
    _recursive( otherFilter._recursive ) {
}

pFilter::~pFilter( ) {
    _values.clear( );
}

QSharedPointer< const pParameter > pFilter::getParameter( ) const {
    return _parameter;
}

void pFilter::setParameter( QSharedPointer< const pParameter > param ) {
    _parameter = param;
}

QSharedPointer< const pParamValue > pFilter::getValue( int index ) const {
    int cnt = _values.count();
    if( index < 0 || index >= cnt )
        return nullptr;

    return _values[index];
}

void pFilter::setValue( QSharedPointer< const pParamValue > pvalue ) {
    if( pvalue.isNull() )
        return;

    _values.clear();
    _values.append( pvalue );
}

void pFilter::addValue( QSharedPointer< const pParamValue > pvalue ) {
    _values.append( pvalue );
}

void pFilter::setValues( const QList< QSharedPointer< const pParamValue > >& pvalues ) {
    _values = pvalues;
}

void pFilter::removeValue( int index ) {
    int cnt = _values.count();
    if( index < 0 || index >= cnt )
        return;

    _values.removeAt( index );
}

void pFilter::clearValues( ) {
    _values.clear( );
}

pFilter::FilterOper pFilter::getOperation( ) const {
    return _oper;
}

void pFilter::setOperation( pFilter::FilterOper oper ) {
    _oper = oper;
}

bool pFilter::isCaseSensitive( ) const {
    return _caseSensitive;
}

void pFilter::setCaseSensitive( bool val ) {
    _caseSensitive = val;
}

bool pFilter::isRecursive( ) const {
    return _recursive;
}

void pFilter::setRecursive( bool val ) {
    _recursive = val;
}

bool pFilter::isCorrect() const {
    bool bCorrect = true;
    
    switch( _oper ){
        //для таких операций возможна работа только с одним значением
        case foEq:
        case foNotEq:
        case foGr:
        case foLess:
        case foGrEq:
        case foLessEq:
        
        case foLike:
        case foLikeIn:
        case foLikeStart:
        case foLikeEnd:
            if(_values.count() != 1)
                bCorrect = false;
            break;
        case foIn:
        case foNotIn:
            if(_values.count() == 0)
                bCorrect = false;
            break;
        case foBetween:
            if(_values.count() != 2)
                bCorrect = false;
            break;
        case foInSQL:
            if(_values.count() != 1)
                bCorrect = false;
            if(_values.at(0)->value().toString().startsWith("select ", Qt::CaseInsensitive) == false)
                bCorrect = false;
            break;
        case foIsNotNull:
        case foIsNull:
            if(_parameter.isNull())
                bCorrect = false;
            break;
        default:
            if(_values.count() != 0)
                bCorrect = false;
            break;
    }

    return bCorrect;
}

QString pFilter::constructForIn() const {
    QString str;

    int cnt = _values.count();
    if( cnt == 0)
        return str;

    for (int i=0; i<_values.count(); i++)
    {
        QSharedPointer<const pParamValue> v = _values[i];
        str += v->valueForInsert();
        if(i<cnt-1)
            str += ", ";
    }

    return str;
}

bool pFilter::operator== (const pFilter& anotherFilter) const {
    bool wres = true;
    if (this->_parameter && anotherFilter._parameter)
        wres = wres && this->_parameter->getId() == anotherFilter._parameter->getId();
    else if( (this->_parameter && !anotherFilter._parameter) ||
             (!this->_parameter && anotherFilter._parameter) )
        return false;
    wres = wres && this->_oper == anotherFilter._oper;
    wres = wres && this->_caseSensitive == anotherFilter._caseSensitive;
    wres = wres && this->_recursive == anotherFilter._recursive;
    wres = wres && this->_values.count() == anotherFilter._values.count();
    for (int i=0; i<this->_values.count() && wres; i++)
        wres = wres && this->_values[i]->value() == anotherFilter._values[i]->value();

    return wres;
}

bool pFilter::operator!= (const pFilter& anotherFilter) const {
    bool iseq (*this == anotherFilter );
    return !iseq;
}
