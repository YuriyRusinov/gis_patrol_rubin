select f_safe_drop_type('h_get_category_types');
create type h_get_category_types as(id int8,
                                    name varchar,
                                    t_desc varchar,
                                    is_qualifier boolean);

create or replace function cGetCategoryType(int8) returns setof h_get_category_types as
$BODY$
declare
    idType alias for $1;
    r h_get_category_types%rowtype;
begin

    for r in
        select 
            id,
            name,
            description,
            (id=1 or id=2 or id=8 or id=9) as is_qualifier
        from
            tbl_category_type
        where
            id = idType  
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function cGetCategoryTypes() returns setof h_get_category_types as
$BODY$
declare
    r h_get_category_types%rowtype;
begin

    for r in
        select 
            id,
            name,
            description,
            (id=1 or id=2 or id=8 or id=9) as is_qualifier
        from
            tbl_category_type
        loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';
