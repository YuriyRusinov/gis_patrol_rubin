drop function if exists createIOTable (varchar, int4, bool);
create or replace function createIOTable (varchar, int8, bool) returns varchar as
$BODY$
declare
    table_name alias for $1;
    id_category alias for $2; --CHILD CATEGORY, NOT MAIN!!!
    bInheritRootTable alias for $3;

    create_pk_query varchar; --creates sequence for primary key
    create_query varchar; --creates the table
    alter_query varchar; --alter the table
    create_ref_table varchar; --create some of reference tables of the category have some attributes with type 17 (atCheckListEx)
    
    query varchar;
    r RECORD;
    res int8;
    amount int8;
    what int8;
    unit varchar;
    c_query varchar;

    s_user varchar; -- session_user
    c_user varchar; -- current user
    
    tName varchar; --for atCheckListEx
    q varchar; --for atCheckListEx
    rr RECORD; --for atCheckListEx
    isExist int8;

    bHasGIS bool; --qualifier has gis attribute!
    bHasParent bool;
    parentCode varchar;

    refColumnName varchar;
begin
    select into res count (*) from pg_tables as t where t.tablename = table_name;
    if (res > 0) then
        raise exception 'entity % (table) already exists in database', table_name;
        return NULL;
    end if;

    select into res count (*) from pg_views as v where v.viewname = table_name;
    if (res > 0) then
        raise exception 'entity % (view) already exists in database', table_name;
        return NULL;
    end if;

    create_pk_query := E'create sequence if not exists ' || table_name || '_id_seq;';
    execute create_pk_query;
    create_query := 'create table ' || table_name || ' (id int8 not null default pg_catalog.nextval(' || quote_literal(table_name || '_id_seq') || '), ';

    query := 'select 
                   a.id, 
                   a.code, 
                   ac.is_mandatory, 
                   ac.default_value, 
                   at.code as atype, 
                   at.id as atypeid, 
                   a.table_name as atabname
               from 
                   tbl_parameters a 
                   inner join tbl_cat_params ac on (a.id = ac.id_parameter and ac.id_category=' || id_category || ' and a.id > 1) 
                   inner join tbl_parameter_types at on (a.id_param_type = at.id);';
    raise warning '%', query;

    alter_query = '';
    create_ref_table = '';
    
    bHasGIS = false;
    bHasParent = false;

    for r in
        execute query
    loop
        
        refColumnName := 'id';

        --atCheckListEx
        if(r.atypeid = 17) then --atCheckListEx
            raise warning '% % %', r.atypeid, table_name, r.atabname;

            tName := table_name || '_' || r.atabname || '_ref_' || r.id;

            --if table is already exist then we just return and do nothing
            q := 'select f_is_table_exist(' || quote_literal(tName) || ', NULL) as is_exist';
            for rr in execute q
            loop
                --TODO: need add check that if the table exist that has the structure aka (id_1 int8, id_2 int8)
                --else we should create the new table
                if(rr.is_exist <> 1) then
                    create_ref_table := create_ref_table || ' create table ' || tName || ' (id_' || table_name || ' int8, id_' || r.atabname || ' int8); ';
                    --На эту таблицу пока проверку на префикс tbl_ делать не надо, ибо она еще не переименована (находится в процессе создания в данном триггере)
                    if( lower(table_name) = 'spatial_ref_sys' ) then
                        create_ref_table := create_ref_table || ' alter table '  || tName || ' ADD CONSTRAINT FK_ID_' || tName || '_1 FOREIGN KEY (ID_' || table_name || ') REFERENCES ' || table_name || ' (srid) ON DELETE CASCADE ON UPDATE CASCADE; ';
                    else
                        create_ref_table := create_ref_table || ' alter table '  || tName || ' ADD CONSTRAINT FK_ID_' || tName || '_1 FOREIGN KEY (ID_' || table_name || ') REFERENCES ' || table_name || ' (ID) ON DELETE CASCADE ON UPDATE CASCADE; ';
                    end if;

                    select f_is_view_exist(r.atabname) into isExist; --Если представление с таким названием существует, то это означает, что реальная таблица имеет название с префиксом tbl_
                    if(isExist = 1) then
                        create_ref_table := create_ref_table || ' alter table '  || tName || ' ADD CONSTRAINT FK_ID_' || tName || '_2 FOREIGN KEY (ID_'|| r.atabname || ') REFERENCES tbl_' || r.atabname || ' (ID) ON DELETE RESTRICT ON UPDATE CASCADE; ';
                    else
                        create_ref_table := create_ref_table || ' alter table '  || tName || ' ADD CONSTRAINT FK_ID_' || tName || '_2 FOREIGN KEY (ID_'|| r.atabname || ') REFERENCES ' || r.atabname || ' (ID) ON DELETE RESTRICT ON UPDATE CASCADE; ';
                    end if;
                    --create_ref_table := create_ref_table || ' select setGrants1(' || quote_literal(tName) || '); ';
                    raise warning 'ref table query is %', create_ref_table;
                end if;
            end loop;

        else   --not many-to-many

            if(r.atypeid = 28) then --GIS-object (data type GEOMETRY)
                bHasGIS = true;
            end if;

            create_query := create_query || '"' || r.code || '" ' || r.atype;

            --mandatory
            if (r.is_mandatory) then
                create_query := create_query || ' not null';
            else
                create_query := create_query || ' null';
            end if;

            --default_value
            if (r.default_value is not null) then
                create_query := create_query || ' default ';

                if (r.atypeid = 4 or r.atypeid = 5) then --DATE OR TIMESTAMP
                    if (r.default_value = 'current_timestamp') then
                        create_query := create_query || ' current_timestamp';
                    else
                        create_query := create_query || ' to_timestamp( ' || quote_literal (r.default_value) || ', ' || quote_literal ('DD.MM.YYYY HH24:MI:SS') || '::timestamp)';
                    end if;
                elsif (r.atypeid = 10) then --INTERVAL
                    if (not is_int4 (split_part (r.default_value, ' ', 1))) then
                        raise exception 'Interval value is invalid';
                        return NULL;
                    end if;

                    amount := split_part (r.default_value, ' ', 1)::int4;
                    unit := split_part (r.default_value, ' ', 2);
                    what := 0;
                    if (lower (unit) = 'years') then
                        what := 1;
                    elsif (lower (unit) = 'half-years') then
                        what := 2;
                    elsif (lower (unit) = 'quarters') then
                        what := 3;
                    elsif (lower (unit) = 'months') then
                        what := 4;
                    elsif (lower (unit) = 'weeks') then
                        what := 5;
                    elsif (lower (unit) = 'days') then
                        what := 6;
                    elsif (lower (unit) = 'hours') then
                        what := 7;
                    elsif (lower (unit) = 'minutes') then
                        what := 8;
                    elsif (lower (unit) = 'seconds') then
                        what := 9;
                    else
                        raise exception 'Invalid unit';
                        return NULL;
                    end if;

                    create_query := create_query || '{' || amount || ',' || what || '}';
                    ---r.default_value;
                    ---TODO : need working.

                elsif (r.atypeid = 12) then -- INT8[]
                    if(substr(r.default_value, 1, 1) <> '{') then
                        create_query := create_query || quote_literal ('{' || r.default_value || '}');
                    else
                        create_query := create_query || quote_literal (r.default_value);
                    end if;
                elsif (r.atypeid = 9 or r.atypeid = 11 or r.atypeid = 14 or r.atypeid = 15) then
                    create_query := create_query || quote_literal (r.default_value);
                else
                    create_query := create_query || r.default_value;
                end if;
            end if;  --defvalue

            create_query = create_query || ', ';
    
            --atList or atParent
            if (r.atypeid = 2 or r.atypeid = 3) then --atList, atParent
                if (alter_query is null) then
                    alter_query := 'ALTER TABLE "' || table_name || '" ADD CONSTRAINT "FK_' || table_name || '_REF_' || r.code || '" foreign key ("' || r.code || '") references ';
                else
                    alter_query := alter_query || 'ALTER TABLE "' || table_name || '" ADD CONSTRAINT "FK_' || table_name || '_REF_' || r.code || '" foreign key ("' || r.code || '") references ';
                end if;
                if (r.atypeid = 3) then
                    alter_query := alter_query || table_name;
                    bHasParent = true;
                    parentCode = r.code;
                else
                    select f_is_view_exist(r.atabname) into isExist; --Если представление с таким названием существует, то это означает, что реальная таблица имеет название с префиксом tbl_
                    if(isExist = 1 and lower( r.atabname ) != 'v_spatial_ref_sys' ) then
                        alter_query := alter_query || 'tbl_' || r.atabname;
                    elsif (isExist = 1 and lower( r.atabname ) = 'v_spatial_ref_sys' ) then
                        alter_query := alter_query || ' spatial_ref_sys';
                    else
                        alter_query := alter_query || r.atabname;
                    end if;
                end if;
                if( lower(r.atabname) = 'v_spatial_ref_sys' ) then
                    alter_query := alter_query || ' ( srid ) on delete restrict on update cascade;';
                else
                    alter_query := alter_query || ' ("' || refColumnName || '") on delete restrict on update cascade;';
                end if;
            end if;
        --i := i+1;
        end if;
    end loop; --main loop
    
    create_query := create_query || ' constraint PK_' || table_name || ' primary key (id)) ';
    create_query := create_query || ';';
    raise warning 'Create query is %', create_query;

    s_user = session_user;

    create_query := create_query || ' alter table ' || table_name || ' owner to ' || s_user;
    --create_query := create_query || '; grant all on ' || table_name || '_id_seq to ' || s_user;
    

    execute create_query;
    if (not FOUND) then
        raise exception E'Cannot create table % \n The  query is %', table_name, create_query;
        return NULL;
    end if;
    if (alter_query is not null and length (alter_query) > 0) then
        execute alter_query;
        if (not FOUND) then
            raise exception 'Cannot create reference';
            return NULL;
        end if;
    end if;

    if(create_ref_table is not null and length (create_ref_table) > 5) then
        execute create_ref_table;
        if(not FOUND) then
            raise exception 'Cannot create reference tables!';
            return NULL;
        end if;
    end if;
    return table_name;
end
$BODY$ 
language 'plpgsql' security definer;
