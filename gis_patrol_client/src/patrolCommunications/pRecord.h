/*
 * @brief Класс описывает запись в БД 
 * pRecord.h
 *
 * (C) НИИ "Рубин"
 * @author
 *  Ю.Л.Русинов
 */

#pragma	once

#include <QString>

class pRecord {
public:
    pRecord();
    pRecord( qint64 id, const QString& name, const QString& desc=QString(), const QString& code = QString() );
    pRecord( const pRecord& r );
    ~pRecord();
};
