select f_safe_drop_type('h_get_int_pair');
create type h_get_int_pair as (
                            id_copy int8,
                            id_rec int8
                        );
drop function if exists getExValuesId(int8, varchar, varchar, varchar) ;
create or replace function getExValuesId(int8, varchar, varchar, varchar) returns setof h_get_int_pair as
$BODY$
declare
    idRecord alias for $1;
    refTable alias for $2;
    mainColumn alias for $3;
    childColumn alias for $4;

    r h_get_int_pair%rowtype;--record;
    q varchar;
--    iValues int8[];
begin

--    iValues := '{}'::int8[];

    if( idRecord is null ) then
        q := 'select ' || mainColumn || ', ' || childColumn || ' from ' || refTable || ' group by ' || mainColumn || ', ' || childColumn || ' order by 1,2;';
    else
        q := 'select ' || mainColumn || ', ' || childColumn || ' from ' || refTable || ' where ' || mainColumn || ' = ' || idRecord || ' group by ' || mainColumn || ', ' || childColumn || ' order by 1,2;';
    end if;

    for r in execute q
    loop
        return next r;--iValues = iValues || r.ids;
    end loop;

    return;-- iValues;

end
$BODY$
language 'plpgsql';


create or replace function getExValuesIdArray(int4, int8, int4) returns int8[] as
$BODY$
declare
    idObject alias for $1;
    idRecord alias for $2;
    idAttribute alias for $3;

    mainTable varchar;
    refTable varchar;
    mainAttr varchar;
    childAttr varchar;
    idChildCategory int4;

    iValues int8[];
begin

    iValues := NULL;--'{}'::int8[];

    select table_name into mainTable from tbl_io_communication_objects_references where id = idObject;
    if(mainTable isnull) then
        return NULL;
    end if;

    select c.id_child into idChildCategory from tbl_communication_categories c, tbl_io_communication_objects_references io where io.id = idObject and io.id_category = c.id;
    if(idChildCategory isnull) then
        return NULL;
    end if;

    select a.table_name into refTable from tbl_parameters a inner join tbl_cat_params ac on ( ac.id_category = idChildCategory and ac.id_parameter = a.id and a.id = idAttribute ); --attribute should be included in gived category!
    if(refTable isnull) then
        return NULL;
    end if;

    mainAttr := 'id_' || mainTable;
    childAttr := 'id_' || refTable;

    refTable := mainTable || '_' || refTable;
    if (refTable = 'organization_work_mode' or 
        refTable = 'table_notifies_io_objects' or
        refTable = 'position_work_mode' or 
        refTable = 'units_work_mode' or 
        refTable = 'io_objects_organization') 
    then                         
        refTable := refTable;
    else
        refTable := refTable || '_ref_' || idAttribute;
    end if;
    

    iValues = getExValuesId(idRecord, refTable, mainAttr, childAttr);

    if(array_upper(iValues, 1) = 0) then
        return NULL;
    end if;
    
    return iValues;

end
$BODY$
language 'plpgsql' security definer;


create or replace function getExValuesId(int4, int8, int4) returns setof int8 as
$BODY$
declare
    idObject alias for $1;
    idRecord alias for $2;
    idAttribute alias for $3;

    r record;
    iValues int8[];
begin

    iValues := NULL;--'{}'::int8[];

    iValues = getExValuesIdArray(idObject, idRecord, idAttribute);

    if(array_upper(iValues, 1) = 0) then
        return;
    end if;

    for r in select unnest(iValues)
    loop
        return next r.unnest;
    end loop;
    
    return;
end
$BODY$
language 'plpgsql' security definer;
