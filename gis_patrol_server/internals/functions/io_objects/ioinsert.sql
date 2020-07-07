drop function if exists ioInsert(varchar, int4, int4, varchar, varchar, varchar, boolean, varchar, int8, int8, varchar, uuid);

create or replace function ioInsert(varchar, 
                                    int8, 
                                    int8, 
                                    varchar, 
                                    varchar, 
                                    varchar, 
                                    boolean,
                                    varchar,
                                    int8,
                                    int8,
                                    varchar,
                                    uuid) returns int8 as
$BODY$
declare
    ioName alias for $1;
    idCategory alias for $2;
    idAuthor alias for $3;
    tableName alias for $4;
    ioDesc alias for $5;
    ioInfo alias for $6;
    isGlobal alias for $7;
    refTableName alias for $8;
    recordFillColor alias for $9;
    recordTextColor alias for $10;
    rIcon alias for $11;
    m_uuid alias for $12;

    idObject int8;
begin

    select into idObject id from tbl_io_communication_objects_references io where io.uuid_t = m_uuid;
    if (idObject is not null and idObject > 0) then
        return idObject;
    end if;
    select getNextSeq('tbl_io_communication_objects_references', 'id') into idObject;

    insert into tbl_io_communication_objects_references (id, 
                            id_category, 
                            id_author, 
                            name, 
                            table_name, 
                            description, 
                            information, 
                            is_system, 
                            insert_time,
                            is_global,
                            ref_table_name,
                            record_fill_color,
                            record_text_color,
                            r_icon,
                            uuid_t)
                   values  (
                            idObject,
                            idCategory,
                            idAuthor,
                            ioName,
                            tableName,
                            ioDesc,
                            ioInfo,
                            false,
                            current_timestamp,
                            isGlobal,
                            refTableName,
                            recordFillColor,
                            recordTextColor,
                            rIcon,
                            m_uuid);


    return idObject;

end
$BODY$
language 'plpgsql';

/*
create or replace function ioInsert(varchar, 
                                    int4, 
                                    int4, 
                                    int4, 
                                    varchar, 
                                    varchar, 
                                    varchar, 
                                    int4, 
                                    varchar, 
                                    int4, 
                                    int4, 
                                    boolean,
                                    int4,
                                    varchar,
                                    int8,
                                    int8,
                                    int4) returns int4 as
$BODY$
declare
    ioName alias for $1;
    idCategory alias for $2;
    idAuthor alias for $3;
    idState alias for $4;
    tableName alias for $5;
    ioDesc alias for $6;
    ioInfo alias for $7;
    idMaclabel alias for $8;
    uniqueID alias for $9;
    idSyncType alias for $10;
    idOrganization alias for $11;
    isGlobal alias for $12;
    idSearchTemplate alias for $13;
    refTableName alias for $14;
    recordFillColor alias for $15;
    recordTextColor alias for $16;
    idType alias for $17;
    --rIcon alias for $18;

    idObject int4;
    rIcon varchar;
begin

    select into idObject id from f_sel_io_objects(uniqueId) io where io.unique_id = uniqueID;
    if (idObject is not null and idObject > 0) then
        return idObject;
    end if;
    select getNextSeq('io_objects', 'id') into idObject;

    rIcon := NULL;

    insert into io_objects (id, 
                            id_io_category, 
                            author, 
                            id_io_state, 
                            name, 
                            table_name, 
                            description, 
                            information, 
                            is_system, 
                            insert_time,
                            id_maclabel,
                            unique_id,
                            id_sync_type,
                            id_owner_org,
                            is_global,
                            id_search_template,
                            ref_table_name,
                            record_fill_color,
                            record_text_color,
                            id_io_type,
                            r_icon)
                   values  (
                            idObject,
                            idCategory,
                            idAuthor,
                            idState,
                            ioName,
                            tableName,
                            ioDesc,
                            ioInfo,
                            false,
                            current_timestamp,
                            idMaclabel,
                            uniqueID,
                            idSyncType,
                            idOrganization,
                            isGlobal,
                            idSearchTemplate,
                            refTableName,
                            recordFillColor,
                            recordTextColor,
                            idType,
                            rIcon);


    return idObject;

end
$BODY$
language 'plpgsql';
*/
