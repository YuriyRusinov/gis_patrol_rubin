#include "gis_patrolresult.h"

GISPatrolResult::GISPatrolResult( )
{
    currentRow = -1;
}

GISPatrolResult::~ GISPatrolResult( )
{
}

QString GISPatrolResult::getColumnNameAsString(int column) const
{
    return QString::fromUtf8(getColumnName(column));
}

int GISPatrolResult::getCellAsInt( int row, int column, bool * ok ) const
{
    QVariant v = getCell(row, column);
    if(v.isValid() == false){if(ok) *ok = false; return 0;}
    return v.toInt(ok);
}

qlonglong GISPatrolResult::getCellAsInt64( int row, int column, bool * ok ) const
{
    QVariant v = getCell(row, column);
    if(v.isValid() == false){if(ok) *ok = false; return 0;}
    return v.toLongLong(ok);
}

bool GISPatrolResult::getCellAsBool( int row, int column, bool * ok ) const
{
    QVariant v;
    if(getCell(row, column) == "t") v = QVariant(true);
    else if(getCell(row, column) == "f") v = QVariant(false);

    if(v.isValid() == false){if(ok)*ok = false; return false;}
    if(ok) *ok = true;
    return v.toBool();
}

QString GISPatrolResult::getCellAsString( int row, int column, bool * ok ) const
{
    QVariant v = getCell(row, column);
    if(v.isValid() == false){
        if(ok)
            *ok = false; 
        return QString::null;
    }
    if(ok)
        *ok = true;
    
    if(getColumnDataType(column) == dtTimestamp){
        QDateTime dt = v.toDateTime();
        QString s = dt.toString("dd.MM.yyyy hh:mm:ss.zzz");
        return s;
    }

    if(v.type() == QVariant::StringList){
        QStringList sl = v.toStringList();
        return sl.join(",");
    }
    return v.toString();
}

double GISPatrolResult::getCellAsDouble( int row, int column, bool * ok ) const
{
    QVariant v = getCell(row, column);
    if(v.isValid() == false){if(ok)*ok = false; return 0.0;}
    return v.toDouble(ok);
}

QStringList GISPatrolResult::getCellAsStringList( int row, int column, bool * ok ) const
{
    QVariant v = getCell(row, column);
    if(v.isValid() == false){if(ok)*ok = false; return QStringList();}
    if(ok)*ok = true;
    return v.toStringList();
}

QDateTime GISPatrolResult::getCellAsDateTime( int row, int column, bool * ok ) const
{
    QVariant v = getCell(row, column);
    if(v.isValid() == false){if(ok)*ok = false; return QDateTime();}
    if(ok)*ok = true;
    return v.toDateTime();
}
