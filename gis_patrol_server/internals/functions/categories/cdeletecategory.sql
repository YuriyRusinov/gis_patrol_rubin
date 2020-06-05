create or replace function cDeleteCategory(int4) returns int4 as
$BODY$
declare
    idCategory alias for $1;
    idChildCat integer;
    r record;
begin

    select id_child into idChildCat from tbl_communication_categories where id = idCategory;

    delete from tbl_cat_params where id_category = idCategory;
    delete from tbl_communication_categories where id = idCategory;
    if (idChildCat is not null) then
        raise warning 'id_child is %', idChildCat;
        perform cDeleteCategory(idChildCat);
    end if;

    return 1;
end
$BODY$
language 'plpgsql' security definer;
