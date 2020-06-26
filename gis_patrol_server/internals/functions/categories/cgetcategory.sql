select f_safe_drop_type('h_get_category');
create type h_get_category as(id int8,
                              id_io_category_type int8,
                              id_child int8,
                              c_name varchar,
                              c_desc varchar,
                              t_name varchar,
                              t_desc varchar,
                              is_main boolean,
                              c_code varchar,
                              is_system boolean,
                              is_global boolean,
                              is_qualifier boolean);

create or replace function cGetCategories() returns setof h_get_category as
$BODY$
declare
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
            true,
            t.id < 3 or (t.id >= 8 and t.id < 10) as is_qualifier
        from 
            tbl_communication_categories c
            inner join tbl_category_type t on ( c.id_category_type = t.id and c.id_child is not null ) order by 1
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetCategory(int8) returns setof h_get_category as
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
            true,
            t.id < 3 or (t.id >= 8 and t.id < 10) as is_qualifier
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
            true,
            t.id < 3 or (t.id >= 8 and t.id < 10) as is_qualifier
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

create or replace function cGetCategoryIO (int8) returns setof h_get_category as
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
            true,
            t.id < 3 or ( t.id >= 8 and t.id < 10 ) as is_qualifier
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

create or replace function cGetParentCategory(int8) returns setof h_get_category as
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
            true,
            t.id < 3 or ( t.id >= 8 and t.id < 10 ) as is_qualifier
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

create or replace function cGetChildCategory(int8) returns setof h_get_category as
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
            true,
            t.id < 3 or ( t.id >= 8 and t.id < 10 ) as is_qualifier
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
