create or replace function ioInsertAttrCheck() returns trigger as
$BODY$
declare
    r record;
    rr record;
    tableName varchar;
    query varchar;
    idOrganization int4;
    cnt int4;
    isExist int4;
    idType int4;
begin

    if(TG_OP = 'UPDATE') then
        if(new.value <> old.value) then
            raise exception 'UPDATE "value" field in tbl_parameter_values disallowed! Realized via insert new record!';
            return NULL;
        end if;
    end if;

    if(TG_OP = 'UPDATE') then
        if(old.is_actual = false) then
            raise exception 'You cannot update attribute values placed in archive!';
            return NULL;
        end if;
    end if;

/*    if(checkIOForOwner(new.id_io_object) = false) then
        return NULL;
    end if;
*/
    select count(*) into cnt from tbl_cat_params where id = new.id_attr_category;
    if(cnt is null or cnt = 0) then
        raise exception 'You cannot add the attribute value to the object because of its category does not contain that!';
        return NULL;
    end if;
    
    if(new.start_time isnull) then
        new.start_time := current_timestamp;
    end if;

    if(new.stop_time isnull) then
        new.is_actual := true;
    else
        if(new.start_time > new.finish_time) then
            raise exception 'start_time of the attribute value cannot be greather then stop_time!';
            return NULL;
        end if;

        if(new.start_time <= current_timestamp and new.finish_time > current_timestamp) then
            new.is_actual := true;
        else
            new.is_actual := false;
        end if;
    end if;

    if(new.is_actual = true) then
        select count(id) into cnt from tbl_parameter_values where id_communication_object=new.id_communication_object and id_param_category = new.id_param_category and is_actual = true and id <> new.id;
        if(cnt > 0) then
            raise exception 'Current version of DynamicDocs Server does not support multiple actual copies of the attribute value! id_io_object = %, id_attr_category = %', new.id_io_object, new.id_attr_category;
            return NULL;
        end if;
    end if;

    if(session_user = 'jupiter') then --information exchange. in that case new.value for complex attrs contains unique_id of attr_attr. We should convert it to ID of attr_attr
        select a.id_param_type into idType 
        from  tbl_parameters a inner join tbl_cat_params ac
            on (a.id = ac.id_parameter and ac.id = new.id_param_category);

        if(idType isnull) then
            raise exception 'Found attribute with NULL type!';
            return NULL;
        end if;

--        if(idType = 32) then --complex attribute
--            new.value = convertAttrAttrValue(new.value);
--        end if;
    end if;


    if(TG_OP = 'INSERT') then
        for r in 
            select a.id, a.id_param_type, a.table_name 
            from tbl_parameters a inner join tbl_cat_params ac on
            ( ac.id = new.id_param_category and ac.id_parameter = a.id )
        loop
            if(r.id_a_type <> 17) then --CheckBoxListEx
                return new;
            end if;

            tableName := 'io_object_' || r.table_name || '_ref_' || r.id;

            --if table is already exist then we just return and do nothing
            query := 'select f_is_table_exist(' || quote_literal(tableName) || ', NULL) as is_exist';
            for rr in execute query
            loop
                if(rr.is_exist = 1) then
                    return new;
                end if;
            end loop;

            --else we should create the new table
            query := 'create table ' || tableName || ' (id_io_object int4, id_' || r.table_name || ' int4); ';
            execute query;
            query := 'alter table ' || tableName || ' ADD CONSTRAINT FK_ID_IO_OBJECT FOREIGN KEY (ID_IO_OBJECT) REFERENCES tbl_IO_OBJECTS (ID) ON DELETE CASCADE ON UPDATE RESTRICT';
            execute query;

            select f_is_view_exist(r.table_name) into isExist;
            if(isExist = 1) then --Если представление существует, то это означает, что реальная таблицйа имеет название с префиксом tbl_
                query := 'alter table ' || tableName || ' ADD CONSTRAINT FK_ID_' || r.table_name || ' FOREIGN KEY (ID_'|| r.table_name || ') REFERENCES tbl_' || r.table_name || ' (ID) ON DELETE RESTRICT ON UPDATE RESTRICT';
            else
                query := 'alter table ' || tableName || ' ADD CONSTRAINT FK_ID_' || r.table_name || ' FOREIGN KEY (ID_'|| r.table_name || ') REFERENCES ' || r.table_name || ' (ID) ON DELETE RESTRICT ON UPDATE RESTRICT';
            end if;
            execute query;

            perform setGrants1(tableName);

        end loop;

        return new;
    end if;

    return new;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgioinsertattr', 'tbl_parameter_values');

select f_create_trigger('trgioinsertattr', 'before', 'insert or update', 'tbl_parameter_values', 'ioinsertattrcheck()');
