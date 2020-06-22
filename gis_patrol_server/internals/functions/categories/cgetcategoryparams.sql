create or replace function cGetCategoryParameter(int8) returns setof h_get_parameter as
$BODY$
declare
    idCategoryParam alias for $1;
    r h_get_parameter%rowtype;
    query varchar;
begin

    query := E'select 
            p.id, 
            ptt.id,
            pgr.id,
            p.code, 
            p.name, 
            p.title, 
            p.table_name, 
            p.column_name, 
            ptt.name, 
            ptt.code, 
            pcat.default_value, 
            pcat.is_mandatory, 
            pcat.is_read_only,
            pcat.param_sort_order
        from
            tbl_cat_params pcat
            inner join tbl_parameters p on (pcat.id = ' || idCategoryParam || E' and pcat.id_parameter = p.id) inner join tbl_parameter_types ptt on (p.id_param_type = ptt.id) inner join tbl_parameters_groups pgr on (p.id_param_group=pgr.id);';
            raise warning '%', query;
    for r in 
        execute query
    loop
        return next r;
    end loop;
    
    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetCategoryParam(int8, int8) returns setof h_get_parameter as
$BODY$
declare
    idCategory alias for $1;
    idParameter alias for $2;

    r h_get_parameter%rowtype;
    query varchar;
begin

    query := E'select 
            p.id, 
            ptt.id,
            pgr.id,
            p.code, 
            p.name, 
            p.title, 
            p.table_name, 
            p.column_name, 
            ptt.name, 
            ptt.code, 
            pcat.default_value, 
            pcat.is_mandatory, 
            pcat.is_read_only,
            pcat.param_sort_order
        from  
            tbl_cat_params pcat
            inner join tbl_parameters p on (pcat.id_category = ' || idCategory || E' and pcat.id_parameter = ' || idParameter || E' and pcat.id_parameter = p.id) 
            inner join tbl_parameter_types ptt on (p.id_param_type = ptt.id) inner join tbl_parameters_groups pgr on (p.id_param_group=pgr.id)'; 
    for r in 
        execute query
    loop
        
        return next r;
    end loop;
    
    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetCategoryParamsByIO(int8) returns setof h_get_parameter as
$BODY$
declare
    idObject alias for $1;

    idCategory int8;
    r h_get_parameter%rowtype;
    query varchar;
begin
    
    select c.id_child into idCategory from tbl_communication_categories c inner join tbl_io_communication_objects_references io on (io.id = idObject and io.id_category = c.id);
    if(idCategory isnull) then
        return;
    end if;

    for r in select * from cGetCategoryParams(idCategory)
    loop
        return next r;
    end loop; 
    return;
    
end
$BODY$
language 'plpgsql';

create or replace function cGetCategoryParamsByTableName(varchar) returns setof h_get_parameter as
$BODY$
declare
    tableName alias for $1;

    idCategory int8;
    r h_get_parameter%rowtype;
    query varchar;
begin
    
    select c.id_child into idCategory from tbl_communication_categories c inner join tbl_io_communication_objects_references io on (io.table_name = tableName and io.id_category = c.id);
    if(idCategory isnull) then
        return;
    end if;

    for r in select * from cGetCategoryParams(idCategory)
    loop
        return next r;
    end loop; 
    return;
    
end
$BODY$
language 'plpgsql';


create or replace function cGetCategoryParams(int8) returns setof h_get_parameter as
$BODY$
declare
    idCategory alias for $1;
    r h_get_parameter%rowtype;
    query varchar;
begin

    query := E'select 
            p.id, 
            ptt.id, 
            pgr.id,
            p.code, 
            p.name, 
            p.title, 
            p.table_name, 
            p.column_name, 
            ptt.name, 
            ptt.code, 
            pcat.default_value, 
            pcat.is_mandatory, 
            pcat.is_read_only,
            pcat.param_sort_order
        from  
            tbl_cat_params pcat inner join tbl_parameters p on (pcat.id_category = ' || idCategory || E' and pcat.id_parameter = p.id) inner join tbl_parameter_types ptt on (p.id_param_type = ptt.id) inner join tbl_parameters_groups pgr on (p.id_param_group=pgr.id)';
    raise warning 'query is %', query;
--(case when a.column_name isnull then NULL else (select a1.id_a_type from attributes a1 where a1.code = a.column_name) end) as ref_attr_type
    for r in 
        execute query
    loop
        return next r;
    end loop;
    
    return;
end
$BODY$
language 'plpgsql';
