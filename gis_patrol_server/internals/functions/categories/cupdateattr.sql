create or replace function cUpdateAttr(int8, int8, varchar, boolean, boolean, int4) returns int8 as
$BODY$
declare
    idCategory alias for $1;
    idParam alias for $2;

    defValue alias for $3;
    isMandatory alias for $4;
    isReadOnly alias for $5;
    paramOrder alias for $6;

    cnt int4;
    idCatParam int8;
begin

    select id into idCatParam from tbl_cat_params where id_category = idCategory and id_parameter = idParam;
    if( idCatParam is not null ) then
        update tbl_cat_params set
            default_value = defValue,
            is_mandatory = isMandatory,
            is_read_only = isReadOnly,
            param_sort_order = paramOrder
        where id = idCatParam;
        return idCatParam;
    end if;

    idCatParam := getNextSeq('tbl_cat_params', 'id');
    insert into tbl_cat_params( id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order)
    values( idCatParam, idCategory, idParam, defValue, isMandatory, isReadOnly, paramOrder );

    if( not FOUND ) then
        return -1;
    end if;

    return idCatParam;

end
$BODY$
language 'plpgsql';
