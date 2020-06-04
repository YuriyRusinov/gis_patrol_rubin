create or replace function getNextSeq(varchar, varchar) returns int8 as
$BODY$
declare
    tableName alias for $1;
    pkName alias for $2;

    id int8;
    seqName varchar;
    seqTableName varchar;
    isExist int4;
begin
    perform clearLastError();

    if (tableName = 'tbl_io_communication_objects_references') then
        seqTableName = 'tbl_communication_objects_references';
    else
        select f_is_view_exist(tableName) into isExist; --if view with given name is exist this means that the real table has name with prefix tbl_
        if(isExist = 1) then
            --seqName := 'tbl_' || tableName || '_' || pkName || '_seq';
            seqTableName := 'tbl_' || tableName;-- || '_' || pkName || '_seq';
        else
            --seqName := tableName || '_' || pkName || '_seq';                
            seqTableName := tableName;-- || '_' || pkName || '_seq';                
        end if;
    end if;


    seqName = seqTableName || '_' || pkName || '_seq';
    select pg_catalog.nextval(seqName) into id;

    if(id isnull) then
        perform updateLastError('UNK0', 'Unknown error was occured');
        return -1;
    end if;
    
    return id;

--    exception when OTHERS
--
--              then 
--                   perform updateLastError(SQLSTATE, SQLERRM);
--                   return -1;
end
$BODY$
language 'plpgsql';
