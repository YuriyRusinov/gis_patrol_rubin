#include <stdarg.h>
#include <QtDebug>

#include "gis_patrolpgdatabase.h"
#include "gis_patrolpgresult.h"
#include "pqnotify.h"

#define SEC_TO_SLEEP 10
#define _REPEAT_COUNT_ 5
#ifdef WIN32
    #define _SLEEP Sleep
    #define _SECONDS_TO_SLEEP_ 1000*SEC_TO_SLEEP
#else
    #include <unistd.h>
    #define _SLEEP sleep
    #define _SECONDS_TO_SLEEP_ SEC_TO_SLEEP
#endif

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::GISPatrolPGDatabase
//
#ifdef USE_NOTIFICATION
GISPatrolPGDatabase::GISPatrolPGDatabase( bool _tolisten ) : notify_conn(NULL), to_listen(_tolisten)
#else
GISPatrolPGDatabase::GISPatrolPGDatabase() : GISPatrolDatabase()
#endif
{
    conn = NULL;
}

GISPatrolPGDatabase::GISPatrolPGDatabase( PGconn * _conn ) : GISPatrolDatabase()
{
    conn = _conn;

    ipServer = PQhost(conn);
    user = PQuser(conn);
    password = PQpass(conn);
    port = PQport(conn);
    database = PQdb(conn);
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::~GISPatrolPGDatabase
//
GISPatrolPGDatabase::~GISPatrolPGDatabase()
{
#ifdef USE_NOTIFICATION
    for( list<KKSNotify*>::iterator ii = notifies.begin(); ii != notifies.end(); ii = notifies.erase(ii) )
        delete *ii;
    stopListen();
#endif
    disconnect(false);
}

//------------------------------------------------------------------------------
//
// PQdatabase::connect
//
bool GISPatrolPGDatabase::connect( QString _ipServer, 
                             QString _database, 
                             QString _user, 
                             QString _password, 
                             QString _port,
                             bool reconnect) const
{
    if ( reconnect )
    {
        disconnect(reconnect);
    }
    if ( connected() )
    {
        return true;
    }

    if ( ! _ipServer.isEmpty() ) ipServer = _ipServer;
    if ( ! _database.isEmpty() ) database = _database;
    if ( ! _user.isEmpty() ) user = _user;
    if ( ! _password.isEmpty() ) password = _password;
    if ( ! _port.isEmpty() ) port = _port;

    conn =  PQsetdbLogin( ipServer.toLatin1().constData(), 
                          port.toLatin1().constData(), 
                          NULL, 
                          NULL,
                          database.toLatin1().constData(), 
                          user.toLatin1().constData(),  
                          password.toLatin1().constData());
    
    if( !connected() ){
        char * err = PQerrorMessage(conn);
        qCritical() << err;

        return connected();
    }

#ifdef USE_NOTIFICATION

    if (to_listen)
    {
        notify_conn = PQsetdbLogin( ipServer.toLatin1().constData(), 
                                    port.toLatin1().constData(), 
                                    NULL, 
                                    NULL,
                                    database.toLatin1().constData(), 
                                    user.toLatin1().constData(), 
                                    password.toLatin1().constData() );

        switch( PQstatus( notify_conn ) )
        {
                case CONNECTION_OK:
                break;

                case CONNECTION_BAD:
                default:
                break;////////Oleg//////////////////
        }
    }
#endif
    
    GISPatrolResult * res = NULL;
    res = execute("set client_encoding to utf8");
    if(!res){
        qCritical("cannot set client_encoding to utf8");
        disconnect(reconnect);
        return connected();
    }
    delete res;

    res = execute("select f_set_all_schemas_visible()");
    if(!res){
        qCritical("cannot set search_path to public, dic, nub");
        disconnect(reconnect);
        return connected();
    }
    delete res;

    res = execute("select createTempTables()");
    if(!res){
        qCritical("cannot execute createTempTables()");
        disconnect(reconnect);
        return connected();
    }
    delete res;

    if(idCurrentDl > 0){
        char * q = new char[100];
        snprintf(q, 99, "select setCurrentDl(%d)", idCurrentDl);
        
        res = execute(q);
        if(!res){
            delete[] q;
            qCritical("cannot execute setCurrentDl()");
            disconnect(reconnect);
            return connected();
        }
        delete[] q;
        delete res;
    }

    return connected();
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::disconnect
//
void GISPatrolPGDatabase::disconnect(bool reconnect) const
{
    idCurrentDl = -1;
    idCurrentUser = -1;

    if ( conn != NULL )
    {
        if(!reconnect){
            GISPatrolResult * res = execute("select f_clear_function();");
            if(!res){
                qCritical("cannot execute f_clear_function!");
            }
        
            delete res;
        }

        PQfinish( conn );
        conn = NULL;
    }

#ifdef USE_NOTIFICATION
    if (!to_listen)
        return;

    if ( notify_conn != NULL )
    {
        PQfinish( notify_conn );
        notify_conn = NULL;
    }
#endif

    emit disconnected();
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::connected
//
bool GISPatrolPGDatabase::connected() const
{
    bool s_conn;
#ifdef USE_NOTIFICATION

    bool  s_notify_conn;

    if (to_listen)
        s_notify_conn = (PQstatus( notify_conn ) == CONNECTION_OK);
#endif

    s_conn = (PQstatus( conn ) == CONNECTION_OK);

#ifdef USE_NOTIFICATION
    return ((to_listen) ? (s_conn && s_notify_conn) : s_conn);
#else
    return s_conn;
#endif
}

#ifdef USE_NOTIFICATION
//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::addListener
//
void GISPatrolPGDatabase::addListener( IKKSListener* listener, const char* notify_name )
{

    // Try to find it in the notifies
    for( list<KKSNotify*>::iterator ii = notifies.begin(); ii != notifies.end(); ii++ )
        if ( strcmp( (*ii)->name.c_str(), notify_name ) == 0 )
        {
            // We are listening it, so add only the listener
            bool isFound = false;
            for( list<IKKSListener*>::iterator jj = (*ii)->listeners.begin(); jj != (*ii)->listeners.end(); jj++ )
            {
                if ( (*jj) == listener )
                {
                    isFound = true;

                    break;
                }
            }
            if ( !isFound )
                (*ii)->listeners.push_back( listener );
            return;
        }

    // Start listen
    char * sql = new char[50 + strlen(notify_name)];
    PGresult* result = NULL;
    sprintf( sql,"LISTEN %s;", notify_name );

    //  if ( PQstatus( notify_conn ) == CONNECTION_BAD )
    //    throw PQexception( "Not Connected" );

    result = PQexec( notify_conn, sql );

    //  if ( PGresultStatus( result ) != PGRES_COMMAND_OK &&
    //       PGresultStatus( result ) != PGRES_TUPLES_OK )
    //    throw PQexception( PQerrorMessage( notify_conn ) );

    PQclear( result );

    // Add notify
    KKSNotify* notify = new KKSNotify();
    notify->name = notify_name;
    notify->listeners.push_back( listener );
    notifies.push_back( notify );

    delete[] sql;

    return;
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::removeListener
//
void GISPatrolPGDatabase::removeListener( IKKSListener* listener, const char* notify_name )
{
    for( list<KKSNotify*>::iterator ii = notifies.begin(); ii != notifies.end(); ii++ ){
        if ( strcmp( (*ii)->name.c_str(), notify_name ) == 0 )
        {
            // Remove notify for the listener
            for( list<IKKSListener*>::iterator jj = (*ii)->listeners.begin(); jj != (*ii)->listeners.end(); jj++ )
                if ( (*jj) == listener )
                {
                    (*ii)->listeners.erase( jj );
                    break;
                }

            if ( (*ii)->listeners.size() > 0) 
                return;

            // If there are no listeners for notify,
            // Stop listen it
            char sql[50];
            PGresult* result = NULL;
            sprintf( sql,"UNLISTEN %s;", notify_name );

            //      if ( PQstatus( notify_conn ) == CONNECTION_BAD )
            //        throw PQexception( "Not Connected" );

            result = PQexec( notify_conn, sql );

            //      if ( PGresultStatus( result ) != PGRES_COMMAND_OK &&
            //           PGresultStatus( result ) != PGRES_TUPLES_OK )
            //        throw PQexception( PQerrorMessage( notify_conn ) );

            PQclear( result );

            // Remove from notifies
            delete *ii;
            notifies.erase( ii );
            if ( notifies.size() == 0) 
                stopListen();
            return;
        }
    }
    return;
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::startListen
//
void GISPatrolPGDatabase::startListen()
{
    if(!notify_conn){
        notify_conn = PQsetdbLogin( ipServer.toLatin1().constData(), 
                                    port.toLatin1().constData(), 
                                    NULL, 
                                    NULL,
                                    database.toLatin1().constData(), 
                                    user.toLatin1().constData(), 
                                    password.toLatin1().constData() );

        switch( PQstatus( notify_conn ) )
        {
                case CONNECTION_OK:
                break;

                case CONNECTION_BAD:
                default:
                break;
        }    }
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::stopListen
//
void GISPatrolPGDatabase::stopListen()
{}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::checkNotifies
//
void GISPatrolPGDatabase::checkNotifies()
{
    //  if ( PQstatus( notify_conn ) != CONNECTION_OK )
    //    throw PQexception( "Not Connected" );

    PGnotify* notify;
    PQconsumeInput( notify_conn );
    while ( ( notify = PQnotifies( notify_conn ) ) != NULL )
    {
        for( list<KKSNotify*>::iterator ii = notifies.begin(); ii != notifies.end(); ii++ ){
            KKSNotify * n = (*ii);
            if(!n)
                continue;

            if ( strcmp( n->name.c_str(), notify->relname ) == 0 )
            {
                for( list<IKKSListener*>::iterator jj = (*ii)->listeners.begin(); jj != (*ii)->listeners.end(); jj++ ){
                    IKKSListener * l = (*jj);
                    if(l)
                        l->notify( notify->relname, notify->extra );
                }
            }
        }
        PQfreemem( notify );
    }
}
#endif /* USE_NOTIFICATION */

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::execute
//
GISPatrolResult* GISPatrolPGDatabase::execute(const char* query ) const
{
    GISPatrolPGResult* _res = NULL;

    if ( ! _exec(query, &_res) )
        return NULL;

    return (GISPatrolResult*)_res;
}

int GISPatrolPGDatabase::sendQuery(const char* query) const
{
    int res = 0;
    res = _sendQuery(query);
    if ( res != 1)
        return 0;

    return res;
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::execParams
//
GISPatrolResult* GISPatrolPGDatabase::execParams(const char* command, 
                                     int nParams, 
                                     const int * paramTypes, 
                                     const char * const * paramValues, 
                                     const int * paramLengths, 
                                     const int * paramFormats, 
                                     int resultFormat ) const
{
    GISPatrolPGResult* _res = NULL;

    PGresult * res = NULL;
    int * internalParamTypes = NULL;

    if(nParams == 0){
        res = _PQexecParams( command,
                             0,
                             NULL,
                             NULL,
                             NULL,
                             NULL,
                             resultFormat
                           );
    }
    else{
        internalParamTypes = new int[nParams];
        for (int i=0; i<nParams; i++)
            internalParamTypes[i] = GISPatrolPGResult::toInternalType((GISPatrolResult::DataType)paramTypes[i]);

        res = _PQexecParams( command,
                             nParams,
                             (const Oid *) internalParamTypes,
                             paramValues,
                             paramLengths,
                             paramFormats,
                             resultFormat
                           );
    }
    _res = new GISPatrolPGResult(res);
    
    if(internalParamTypes) 
            delete[] internalParamTypes;
    
    GISPatrolResult::ResultStatus status = (_res)->resultStatus();

    if ( status != GISPatrolResult::CommandOk && status != GISPatrolResult::TuplesOk )
    {
        fprintf(stderr, "PQdatabase: %s SQL: %s\n", _res->errorMessage().toLocal8Bit().constData(), command);
        qCritical() << _res->errorMessage() << " SQL: " << command;
        delete _res;
        return NULL;
    }

    return (GISPatrolResult*)_res;
}

/*
 * under MCBC, где стоит Postgresql 7.4 функции PQprepare нет
 * поэтому метод закомментирован
 */

GISPatrolResult * GISPatrolPGDatabase::prepare(
                                const char* stmtName, 
                                const char * query,
                                int nParams, 
                                const int * paramTypes
                                ) const
{
    GISPatrolPGResult* _res = NULL;

    PGresult * res = NULL;
    int * internalParamTypes = NULL;

    if(nParams == 0){
        res = PQprepare(  conn,
                          stmtName,
                          query,
                          0,
                          NULL
                       );
    }
    else{
        internalParamTypes = new int[nParams];
        for (int i=0; i<nParams; i++)
            internalParamTypes[i] = GISPatrolPGResult::toInternalType((GISPatrolResult::DataType)paramTypes[i]);

        res = PQprepare(  conn,
                              stmtName,
                             query,
                             nParams,
                             (const Oid *) internalParamTypes
                           );
    }
    _res = new GISPatrolPGResult(res);
    
    if(internalParamTypes) 
            delete[] internalParamTypes;
    
    GISPatrolResult::ResultStatus status = (_res)->resultStatus();

    if ( status != GISPatrolResult::CommandOk && status != GISPatrolResult::TuplesOk )
    {
        fprintf(stderr, "PQdatabase: %s SQL: %s\n", _res->errorMessage().toLocal8Bit().constData(), query);
        qCritical() << _res->errorMessage() << " SQL: " << query;
        delete _res;
        return NULL;
    }

    return (GISPatrolResult*)_res;

}


GISPatrolResult * GISPatrolPGDatabase::execPrepared(
                                        const char* stmtName, 
                                        int nParams, 
                                        const char * const * paramValues, 
                                        const int * paramLengths, 
                                        const int * paramFormats, 
                                        int resultFormat
                                       ) const
{
    GISPatrolPGResult* _res = NULL;

    PGresult * res = NULL;

    if(nParams == 0){
        res = _PQexecPrepared( stmtName,
                               0,
                               NULL,
                               NULL,
                               NULL,
                               resultFormat
                             );
    }
    else{

        res = _PQexecPrepared( stmtName,
                               nParams,
                               paramValues,
                               paramLengths,
                               paramFormats,
                               resultFormat
                             );
    }
    _res = new GISPatrolPGResult(res);
        
    GISPatrolResult::ResultStatus status = (_res)->resultStatus();

    if ( status != GISPatrolResult::CommandOk && status != GISPatrolResult::TuplesOk )
    {
        qCritical() << _res->errorMessage();
        delete _res;
        return NULL;
    }

    return (GISPatrolResult*)_res;
}


//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::begin
//
bool GISPatrolPGDatabase::begin() const
{
    GISPatrolResult* tempres;

    tempres = execute( "BEGIN");// ISOLATION LEVEL SERIALIZABLE" );

    if(tempres){
        delete tempres;
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::commit
//
bool GISPatrolPGDatabase::commit() const
{
    GISPatrolResult* tempres;

    tempres = execute( "COMMIT" );

    if(tempres){ 
        delete tempres;
        return true;
    }

    return false;
}

//------------------------------------------------------------------------------
//
// GISPatrolPGDatabase::rollback
//
bool GISPatrolPGDatabase::rollback() const
{
    GISPatrolResult* tempres;

    tempres = execute( "ROLLBACK" );

    if(tempres){
        delete tempres;
        return true;
    }

    return false;
}

void GISPatrolPGDatabase::createSavePoint(const char * savePointName) const
{
    if(!savePointName){
        execute("SAVEPOINT new_gis_patrol_savepoint");
        return;
    }

    char * query  = new char[30 + strlen(savePointName)];
    strcpy(query, "SAVEPOINT ");
    strcat(query, savePointName);
    execute(query);
}

void GISPatrolPGDatabase::releaseSavePoint(const char * savePointName) const
{
    if(!savePointName){
        execute("RELEASE SAVEPOINT new_gis_patrol_savepoint");
        return;
    }

    char * query  = new char[30 + strlen(savePointName)];
    strcpy(query, "RELEASE SAVEPOINT ");
    strcat(query, savePointName);
    execute(query);
}

void GISPatrolPGDatabase::rollbackToSavePoint(const char * savePointName) const
{
    if(!savePointName){
        execute("ROLLBACK TO SAVEPOINT new_gis_patrol_savepoint");
        return;
    }

    char * query  = new char[30 + strlen(savePointName)];
    strcpy(query, "ROLLBACK TO SAVEPOINT ");
    strcat(query, savePointName);
    execute(query);
}


unsigned int GISPatrolPGDatabase::importBlob(const char * fileName, 
                                       const char * tableName, 
                                       const char * blobColumnName, 
                                       const char * keyColumnName, 
                                       int id, 
                                       bool needDeletePrevious)
{
    begin();
    FILE * f = fopen(fileName, "r");
    if(!f)
    {
        rollback();
        return 0;
    }
    fclose(f);
    Oid oid = lo_import(conn, fileName);
    
    if(needDeletePrevious){
        GISPatrolResult * res = execSQL("select lo_unlink(%s) from %s where %s = %d;", blobColumnName, tableName, keyColumnName, id);
        if(!res || res->resultStatus() != GISPatrolResult::TuplesOk){
            if(res) delete res;
            rollback();
            return 0;
        }
    }
    
    GISPatrolResult * res = execSQL("update %s set %s = %d where %s = %d", tableName, blobColumnName, (int)oid, keyColumnName, id);
    if(!res || (res->resultStatus() != GISPatrolResult::CommandOk && res->resultStatus() != GISPatrolResult::TuplesOk)){
        if(res) delete res;
        rollback();
        return 0;
    }
    
    commit();
    return oid;
}

int GISPatrolPGDatabase::exportBlob(const char * tableName, 
                              const char * blobColumnName, 
                              const char * keyColumnName, 
                              int id, 
                              const char * fileName)
{
    begin();
    FILE * f = fopen(fileName, "w");
    if(!f)
    {
        rollback();
        return 0;
    }
    fclose(f);
    GISPatrolResult * res = execSQL("select %s from %s where %s = %d", blobColumnName, tableName, keyColumnName, id);
    if(!res || (res->resultStatus() != GISPatrolResult::CommandOk && res->resultStatus() != GISPatrolResult::TuplesOk)){
        if(res) delete res;
        rollback();
        return 0;
    }
    int oid = res->getCellAsInt(0, 0);
    int result = lo_export(conn, oid, fileName);
    commit();
    return result;
}

GISPatrolResult * GISPatrolPGDatabase::execSQL( const char * query, ... ) const
{
    QString s;
    va_list ap;

    va_start(ap, query);
    s = s.vsprintf(query, ap);
    va_end(ap);
    
    return GISPatrolDatabase::execute(s);
}

bool GISPatrolPGDatabase::_exec( const char * sql, GISPatrolPGResult ** _res ) const
{
    if ( ! _res )
        return false;

    if ( *_res )
        delete *_res;

    *_res = new GISPatrolPGResult(_PQexec( sql ));

    GISPatrolResult::ResultStatus status = (*_res)->resultStatus();

    if ( status != GISPatrolResult::CommandOk && status != GISPatrolResult::TuplesOk )
    {
        //fprintf(stderr, "PQdatabase: %s SQL: %s\n", (*_res)->errorMessage().toLocal8Bit().constData(), sql);
        qCritical("PQdatabase: %s SQL: %s\n", (*_res)->errorMessage().toLocal8Bit().constData(), sql);
        delete *_res;
        return false;
    }

    return true;
}


int GISPatrolPGDatabase::_sendQuery( const char * sql ) const
{
    int _res = PQsendQuery( conn, sql );
    return _res;

}

bool GISPatrolPGDatabase::connect( bool reconnect ) const
{
    return connect(ipServer,database,user,password, port, reconnect);
}

char * GISPatrolPGDatabase::escapeAsciiString(const char * fromString) const
{
    Q_UNUSED(fromString);

    return NULL;
}

QString GISPatrolPGDatabase::escapeBinaryString (const unsigned char * fromString) const
{
    size_t esc_size;
    size_t fromSize = strlen((char *)fromString);
    unsigned char *esc = /*(char *)*/PQescapeBytea/*Conn*/ (/*conn,*/ fromString, fromSize, &esc_size);
    QString res ((char *)esc);
    PQfreemem (esc);

    return res;
}

GISPatrolResult* GISPatrolPGDatabase::declare(QString cursor_name, QString sql_string) const
{
    GISPatrolResult* tempres;

    QString str = "";
    str = "DECLARE " + cursor_name + " SCROLL CURSOR FOR " + sql_string;

    tempres = execute( str.toLatin1().constData() );

    return tempres;
}

GISPatrolResult* GISPatrolPGDatabase::fetch(QString cursor_name, int direction, int count_str) const
{
//FETCH [ direction { FROM | IN } ] cursorname
    GISPatrolResult* tempres;

    QString str = "";

    switch(direction)
    {
        case 0:
            str = "fetch NEXT from " + cursor_name;
            break;
        case 1:
            str = "fetch PRIOR from " + cursor_name;
            break;
        case 2:
            str = "fetch FIRST from " + cursor_name;
            break;
        case 3:
            str = "fetch LAST from " + cursor_name;
            break;
        case 4:
            str = QString("fetch ABSOLUTE %1 from ").arg(count_str) + cursor_name;
            break;
        case 5:
            str = QString("fetch RELATIVE  %1 from ").arg(count_str) + cursor_name;
            break;
        case 6:
            str = QString("fetch %1 from ").arg(count_str) + cursor_name;
            break;
        case 7:
            str = "fetch ALL from " + cursor_name;
            break;
        case 8:
            str = "fetch FORWARD from " + cursor_name;
            break;
        case 9:
            str = QString("fetch FORWARD %1 from ").arg(count_str) + cursor_name;
            break;
        case 10:
            str = "fetch FORWARD ALL from " + cursor_name;
            break;
        case 11:
            str = "fetch BACKWARD from " + cursor_name;
            break;
        case 13:
            str = "fetch BACKWARD ALL from " + cursor_name;
            break;
        case 12:
            str = QString("fetch BACKWARD %1 from ").arg(count_str) + cursor_name;
            break;
        default:
            str = "";
    }

    tempres = execute( str.toLatin1().constData() );

     return tempres;
}

GISPatrolResult* GISPatrolPGDatabase::close(QString cursor_name) const
{
//  CLOSE ?????? 

    GISPatrolResult* tempres;

    QString str = "";
    str = "CLOSE " + cursor_name;

    tempres = execute( str.toLatin1().constData() );
    commit();
    
    return tempres;
}

GISPatrolResult* GISPatrolPGDatabase::move(QString cursor_name, int direction, int count_str) const
{
    GISPatrolResult* tempres;

    QString str = "";

    switch(direction)
    {
        case 0:
            str = "move NEXT from " + cursor_name;
            break;
        case 1:
            str = "move PRIOR from " + cursor_name;
            break;
        case 2:
            str = "move FIRST from " + cursor_name;
            break;
        case 3:
            str = "move LAST from " + cursor_name;
            break;
        case 4:
            str = QString("move ABSOLUTE %1 from ").arg(count_str) + cursor_name;
            break;
        case 5:
            str = QString("move RELATIVE  %1 from ").arg(count_str) + cursor_name;
            break;
        case 6:
            str = QString("move %1 from ").arg(count_str) + cursor_name;
            break;
        case 7:
            str = "move ALL from " + cursor_name;
            break;
        case 8:
            str = "move FORWARD from " + cursor_name;
            break;
        case 9:
            str = QString("move FORWARD %1 from ").arg(count_str) + cursor_name;
            break;
        case 10:
            str = "move FORWARD ALL from " + cursor_name;
            break;
        case 11:
            str = "move BACKWARD from " + cursor_name;
            break;
        case 13:
            str = "move BACKWARD ALL from " + cursor_name;
            break;
        case 12:
            str = QString("move BACKWARD %1 from ").arg(count_str) + cursor_name;
            break;
        default:
            str = "";
    }

    tempres = execute( str.toLatin1().constData() );

    return tempres;
}

char * GISPatrolPGDatabase::lastError()  const
{
    return PQerrorMessage(conn);
}

//------------------------------------------------------------------------------
//for rod web
// PQdatabase::connect_s
//
bool GISPatrolPGDatabase::connect_s(	string _ipServer, 
								string _database, 
								string _user, 
								string _password, 
								string _port,
                                bool reconnect)
{


	return connect(QString(_ipServer.c_str()),
		QString(_database.c_str()),
		QString(_user.c_str()), 
		QString(_password.c_str()), 
		QString(_port.c_str()), 
		reconnect);


}

PGresult * GISPatrolPGDatabase::_PQexecParams(const char *command,
	                                    int nParams,
	                                    const Oid *paramTypes,
	                                    const char *const * paramValues,
	                                    const int *paramLengths,
	                                    const int *paramFormats,
                                        int resultFormat) const
{
    PGresult * res;
    res = PQexecParams(conn, command, nParams, paramTypes, paramValues, paramLengths, paramFormats, resultFormat);
    if(res)
        return res;

    return res;
}

PGresult * GISPatrolPGDatabase::_PQexecPrepared(const char *stmtName,
                                          int nParams,
                                          const char *const * paramValues,
                                          const int *paramLengths,
                                          const int *paramFormats,
                                          int resultFormat) const
{
    PGresult * res;
    res = PQexecPrepared(conn, stmtName, nParams, paramValues, paramLengths, paramFormats, resultFormat);
    return res;
}

PGresult * GISPatrolPGDatabase::_PQexec(const char *query) const
{
    PGresult * res;
    res = PQexec(conn, query);
    int resStatus = PQresultStatus(res);
    if( resStatus == PGRES_FATAL_ERROR )
    {
    }
    else{
        return res;
    }

    //try to reconnect if disconnected
    int cStatus = PQstatus(conn);
    int i=0;
    if(cStatus != CONNECTION_OK){
        bool ok = false;
        do{
            ok = GISPatrolPGDatabase::connect(true);
            if(ok){
                break;
            }
            _SLEEP(_SECONDS_TO_SLEEP_);
            i++;
        }while(i<_REPEAT_COUNT_);
        
        res = PQexec(conn, query);
    }

    return res;
}
