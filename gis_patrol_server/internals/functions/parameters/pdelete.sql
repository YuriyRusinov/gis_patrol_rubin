create or replace function pDelete(int4) returns int4 as
$BODY$
declare
    idParameter alias for $1;
    cnt int4;
begin
    select count (*) into cnt from tbl_cat_params pcat where pcat.id_parameter = idParameter;
    if (cnt > 0) then
        raise exception 'Cannot remove parameter in category';
        return -1;
    end if;
    delete from tbl_parameters where id=idParameter;
    return 1;

end
$BODY$
language 'plpgsql';
