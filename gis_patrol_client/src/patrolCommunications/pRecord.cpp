/*
 * @brief Класс описывает запись в БД 
 * pRecord.cpp
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#include "pRecord.h"

pRecord::pRecord() {
}

pRecord::pRecord( qint64 id, const QString& name, const QString& desc, const QString& code ) {
    Q_UNUSED( id );
    Q_UNUSED( name );
    Q_UNUSED( desc );
    Q_UNUSED( code );
}

pRecord::pRecord( const pRecord& r ) {
    Q_UNUSED( r );
}

pRecord::~pRecord() {
}
