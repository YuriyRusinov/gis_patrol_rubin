create or replace function cDelAttr(int8, int8) returns int8 as
$BODY$
declare
    idCategory alias for $1;
    idParam alias for $2;

    idCatParam int8;
begin
    select id into idCatParam from tbl_cat_params where id_category = idCategory and id_parameter = idParam;
    if( idCatParam is not null ) then
        delete from tbl_cat_params where id = idCatParam;
        return idCatParam;
    end if;

    return -1;
end
$BODY$
language 'plpgsql';
