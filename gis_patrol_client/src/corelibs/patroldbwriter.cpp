/*
 * @brief Записывальщик данных в БД приложения "Защита-дозор"
 * patroldbwriter.cpp
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

#include "patroldbwriter.h"

pDBWriter::pDBWriter( GISPatrolDatabase* db, QObject* parent )
    : QObject( parent ),
    _db( db ) {
}

pDBWriter::~pDBWriter() {
    _db = nullptr;
}

GISPatrolDatabase* pDBWriter::getDb() const {
    return _db;
}

void pDBWriter::setDb( GISPatrolDatabase* db ) {
    _db = db;
}
