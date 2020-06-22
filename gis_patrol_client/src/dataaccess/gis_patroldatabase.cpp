
#include "gis_patroldatabase.h"
#include "defines.h"

int GISPatrolDatabase::executeCmd(const QString & sql) const
{
    GISPatrolResult * res = execute(sql);
    if(!res || res->resultStatus() != GISPatrolResult::CommandOk){
        if(res){
            delete res;
        }
        return ERROR_CODE;
    }
    delete res;

    return OK_CODE;
}

GISPatrolResult * GISPatrolDatabase::execute( const QString & query ) const
{
    return execute( query.toUtf8().constData() );
}

GISPatrolResult * GISPatrolDatabase::execParams(
                                        const QString          & _command, 
                                        const QList<GISPatrolResult::DataType>       & _paramTypes, 
                                        const QList<QVariant>  & _paramValues,
                                        const QList<int>       & _paramFormats, 
                                        int                      _resultFormat
                                      ) const
{
    if( _paramTypes.count() != _paramFormats.count() || _paramTypes.count() != _paramValues.count()) return NULL;

    QByteArray b = _command.toLatin1();
    const char * command      = b.constData();    
    int          nParams      = _paramTypes.size();
    int          resultFormat = _resultFormat;
    
    int  * paramTypes = new int[nParams];
    int  * paramLengths = new int[nParams]; 
    int  * paramFormats = new int[nParams];
    char ** paramValues = new char * [nParams];

    for(int i=0; i<nParams; i++){
        paramTypes[i]   = _paramTypes.at(i);
        paramFormats[i] = _paramFormats.at(i);

        if(paramFormats[i] == 0){ 
            QByteArray b = _paramValues.at(i).toString().toLatin1();
            paramLengths[i] = b.length();
            paramValues[i] = new char[paramLengths[i]];
            memset(paramValues[i], 0, paramLengths[i]+1);
            memcpy(paramValues[i], b.constData(), paramLengths[i]);
        }
        else{
            QByteArray bytea = _paramValues.at(i).toByteArray();
            paramLengths[i]  = bytea.length();
            paramValues[i] = new char[paramLengths[i]+1];
            memset(paramValues[i], 0, paramLengths[i]+1);
            memcpy(paramValues[i], bytea.constData(), paramLengths[i]);
        }
    }
    
    GISPatrolResult * res = execParams(command, nParams, paramTypes, paramValues, paramLengths, paramFormats, resultFormat);

    delete[] paramTypes;
    delete[] paramLengths;
    delete[] paramFormats;
    //for(int i=0; i<nParams; i++)
        //delete paramValues[i];
    delete[] paramValues;
    
    return res;
}
