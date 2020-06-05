create or replace function cFindEqual(varchar, varchar, varchar, int4, int4, boolean) returns int4 as
$BODY$
declare
    cName alias for $1;
    cCode alias for $2;
    cDesc alias for $3;
    idType alias for $4;
    idChild alias for $5;
    isMain alias for $6;
    
    idCategory int4;
    idChildCategory int4;
    r RECORD;
    
begin
    
    for r in 
        select id from tbl_communication_categories
        where
            id_category_type = idType
            and is_main = isMain
            and name = cName
            and code = cCode
            and (case when cDesc is not null then description = cDesc else description isnull end)
            and (case when idChild is not null then id_child = idChild else id_child isnull end)
    loop
        idCategory := r.id;
        raise notice 'Found EQUAL CATEGORY!';
        return idCategory;

    end loop;

    return -1;
    
end
$BODY$
language 'plpgsql';
