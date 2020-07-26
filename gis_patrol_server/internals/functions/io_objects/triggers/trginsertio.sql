CREATE OR REPLACE FUNCTION ioinsertcheck()   RETURNS trigger AS
$BODY$
declare
    idMaclabel int4;
--    m maclabel;
--    m1 maclabel;
    isGlobal bool;
    idChild int4;
begin
    
    if(TG_OP = 'UPDATE') then
        if(new.id_author <> old.id_author) then
            return NULL; 
        end if;
        
        if(not new.is_global  and old.is_global ) then
            raise exception 'Change global object to nonglobal is not allowed!';
            return NULL;
        end if;
    end if;

    if(new.uuid_t isnull) then
        new.uuid_t = generateUUID();
    end if;
/*
    if(new.last_update isnull) then
        new.last_update = clock_timestamp();
    end if;
*/
/*
    if(new.is_global) then
        select is_global into isGlobal from tbl_communication_categories where id = new.id_category;
        if(isGlobal isnull or not isGlobal) then
            raise exception 'You cannot create global object on nonglobal category!';
            return NULL;
        end if;
    end if;

    if(new.id_io_type isnull) then
        new.id_io_type := 1;
    end if;
    
    if(getCurrentUser() <> 1 and getCurrentUser() <> 2) then --not admin and jupiter
        new.information := getAuthorInfo();
    end if;
*/
    if(new.information isnull) then
        new.information := getAuthorInfo();
    end if;

    --данный блок кода был перенесен из триггера-after, чтобы избежать ошибки с уникальным индексом на поле table_name
    if(TG_OP = 'INSERT') then
        select into idChild id_child from tbl_communication_categories c where c.id = new.id_category;

        if (new.table_name is null and idChild is null) then
            return new;
        elsif (new.table_name is not null and idChild is null ) then
            raise exception 'Invalid table parameters';
            return NULL;
        elsif (new.table_name is null and idChild is not null) then
            new.table_name := 'eio_table_' || new.id;
        end if;

        new.table_name = getRealTableName(new.table_name, new.id);
        if(new.table_name is null) then
            raise exception 'Cannot generate table with given name! -- %', new.table_name;
            return NULL;
        end if;
        if( new.insert_time is null ) then
            new.insert_time = current_timestamp;
            return new;
        end if;

    end if;

    return new;

end
$BODY$
LANGUAGE 'plpgsql';

select f_safe_drop_trigger('trgioinsert', 'tbl_io_communication_objects_references');

select f_create_trigger('trgioinsert', 'before', 'insert or update', 'tbl_io_communication_objects_references', 'ioinsertcheck()');

/*
create trigger trgIOInsert 
before insert or update
on tbl_tbl_io_communication_objects_references 
for each row 
execute procedure ioInsertCheck();
*/

create or replace function ioInsertCheckTableAfter() returns trigger as
$BODY$
declare
    table_name varchar;
    id_category int4;
    id_io_child_category int4;

    real_table_name varchar;
    id_obj int4;
    id_log int4;
    query varchar;
begin
    table_name := new.table_name;
    id_category := new.id_category;
    id_obj := new.id;

    if (new.table_name is null) then
        return new;
    end if;

    select into id_io_child_category id_child from tbl_communication_categories c where c.id = new.id_category;
   
    --в триггере, который на before осуществляется проверка корректности названия подчиненной таблицы
    --и присвоение ей уникального названия при необходимости
    --ранее этот код был тут, однако поскольку возникала ошибка с уникальным индексом на данное поле, то 
    --этот блок кода был перенесен в триггер-before

/*    if(new.ref_table_name is not null) then
        if(isApplicable(new.id_search_template, id_io_child_category) = FALSE) then
            raise exception 'Given search template is not applicable for tables created on the current table category! ID_SEARCH_TEMPLATE = %, ID_CHILD_CATEGORY = %', new.id_search_template, id_io_child_category;
            return NULL;
        end if;

        real_table_name = createIOView (table_name, id_io_child_category, new.id_search_template, new.ref_table_name);
        table_name = real_table_name;
    else
*/
--        new.id_search_template = NULL;
    new.ref_table_name = null;
    real_table_name = createIOTable (table_name, id_io_child_category, true);
    table_name = real_table_name;
--    end if;
    
    if (table_name is null) then
        raise exception 'Cannot create table or view %', table_name;
        return NULL;
    end if;

    if((new.table_name isnull and table_name is not null) or table_name <> new.table_name) then
        query := 'update tbl_io_communication_objects_references set table_name = ' || quote_literal (table_name) || ' where id = ' || id_obj;
--        select into id_log setAsNotLogging (2);
        execute query;
--        select into id_log setAsLogging (2);
    end if;
    
    new.table_name = table_name;

    return new;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('zz_trgzioinserttableafter', 'tbl_io_communication_objects_references');

select f_create_trigger('zz_trgzioinserttableafter', 'after', 'insert', 'tbl_io_communication_objects_references', 'ioinsertchecktableafter()');

