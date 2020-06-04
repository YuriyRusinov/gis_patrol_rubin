select f_safe_drop_type('h_get_object');
create type h_get_object as (id int4,
                             id_io_category int4,
                             author int4,
                             io_name varchar,
                             io_table_name varchar,
                             io_desc varchar,
                             io_info varchar,
                             is_system boolean,
                             insert_time timestamp,
                             is_global boolean,
                             record_fill_color int8,
                             record_text_color int8,
                             ref_table_name varchar,
                             author_email varchar,
                             r_icon varchar,
                             uuid_t uuid);
                             
create or replace function ioGetObject(int4) returns setof h_get_object as
$BODY$
declare
    idObject alias for $1;
    r h_get_object%rowtype;
begin

    for r in 
        select
            io.id,
            io.id_category,
            io.id_author,
            io.name,
            io.table_name,
            io.description,
            io.information,
            io.is_system,
            io.insert_time,
            io.is_global,
            io.record_fill_color,
            io.record_text_color,
            io.ref_table_name,
            u.email,
            io.r_icon,
            io.uuid_t
        from
            tbl_io_communication_objects_references io
            left join users u on (io.id_author = u.id)
            --io_objects io
        where
            io.id = idObject
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function ioGetObjectIDByTableName (varchar) returns int4 as
$BODY$
declare
    tableName alias for $1;
    idObject int4;
begin
    select into idObject io.id from tbl_io_communication_objects_references io where io.table_name = tableName;
    --raise notice '%', idObject;

    if (idObject is null) then
        select id_io_object into idObject from object_ref_tables where table_name = tableName;
        if(idObject is null)  then
            idObject := -1;
        end if;
    end if;

    return idObject;
end
$BODY$
language 'plpgsql';

create or replace function ioGetTableNameByUUID(varchar) returns varchar as
$BODY$
declare
    theUUID alias for $1;
    tableName varchar;
begin
    select table_name into tableName from tbl_io_communication_objects_references io where io.uuid_t = theUUID::uuid;

    return tableName;
end
$BODY$
language 'plpgsql';
