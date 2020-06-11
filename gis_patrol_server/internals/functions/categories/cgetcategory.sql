select f_safe_drop_type('h_get_category');
create type h_get_category as(id int4,
                              id_io_category_type int4,
                              id_child int4,
                              c_name varchar,
                              c_desc varchar,
                              t_name varchar,
                              t_desc varchar,
                              is_main boolean,
                              c_code varchar,
                              is_system boolean,
                              is_global boolean);

create or replace function cGetCategory(int4) returns setof h_get_category as
$BODY$
declare
    idCategory alias for $1;
    r h_get_category%rowtype;
begin

    for r in
        select 
            c.id, 
            c.id_category_type, 
            c.id_child, 
            c.name, 
            c.description, 
            t.name, 
            t.description, 
            c.is_main, 
            c.code,
            c.is_system,
            true
        from 
            tbl_communication_categories c
            inner join tbl_category_type t on (c.id_category_type = t.id and c.id = idCategory)
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetCategory (varchar) returns setof h_get_category as
$BODY$
declare
    tableName alias for $1;
    r h_get_category%rowtype;
begin

    for r in
        select distinct
            cc.id, 
            cc.id_category_type, 
            cc.id_child, 
            cc.name, 
            cc.description, 
            t.name, 
            t.description, 
            cc.is_main, 
            cc.code,
            cc.is_system,
            true
        from 
            tbl_io_communication_objects_references io
            inner join tbl_communication_categories c on (c.id = io.id_category and io.table_name = tableName)
            inner join tbl_communication_categories cc on (c.id_child = cc.id)
            inner join tbl_category_type t on (cc.id_category_type = t.id)
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetCategoryIO (int4) returns setof h_get_category as
$BODY$
declare
    idObject alias for $1;
    r h_get_category%rowtype;
begin

    for r in
        select distinct
            c.id, 
            c.id_category_type, 
            c.id_child, 
            c.name, 
            c.description, 
            t.name, 
            t.description, 
            c.is_main, 
            c.code,
            c.is_system,
            true
        from 
            tbl_communication_categories c inner join
            tbl_category_type t on (c.id_category_type = t.id)
            inner join tbl_io_communication_objects_references io on (c.id = io.id_category and io.id = idObject)
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetParentCategory(int4) returns setof h_get_category as
$BODY$
declare
    idCategory alias for $1;
    r h_get_category%rowtype;
begin

    for r in
        select 
            c.id, 
            c.id_category_type, 
            c.id_child, 
            c.name, 
            c.description, 
            t.name, 
            t.description, 
            c.is_main, 
            c.code,
            c.is_system,
            true
        from 
            tbl_communication_categories c inner join
            tbl_category_type t on (c.id_category_type = t.id and c.id_child = idCategory)
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetChildCategory(int4) returns setof h_get_category as
$BODY$
declare
    idCategory alias for $1;
    r h_get_category%rowtype;
begin

    for r in
        select 
            cc.id, 
            cc.id_category_type, 
            cc.id_child, 
            cc.name, 
            cc.description, 
            t.name, 
            t.description, 
            cc.is_main, 
            cc.code,
            cc.is_system,
            true
        from 
            tbl_communication_categories c
            inner join tbl_communication_categories cc on (c.id_child = cc.id and c.id = idCategory)
            inner join tbl_category_type t on (cc.id_category_type = t.id)
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';