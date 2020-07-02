drop function if exists caddattr(int4, int4, varchar, boolean, boolean);
drop function if exists caddattr(int4, int4, varchar, boolean, boolean, int4);
create or replace function cAddAttr(int8, int8, varchar, boolean, boolean, int4) returns int8 as
$BODY$
declare
    idCategory alias for $1;
    idParameter alias for $2;
    defValue alias for $3;
    isMandatory alias for $4;
    isReadOnly alias for $5;
    acOrder alias for $6;

    cnt int4;
    r record;
    idCategoryParam int8;
begin

    idCategoryParam := NULL;
    for r in 
        select 
            id, default_value, is_mandatory, is_read_only, param_sort_order
        from tbl_cat_params 
        where
           id_category = idCategory and id_parameter = idParameter
    loop
        idCategoryParam := r.id;
        
        if(idCategoryParam is not null) then
            if(r.default_value <> defValue or r.is_mandatory <> isMandatory or r.is_read_only <> isReadOnly or r.param_sort_order <> acOrder) then
                update tbl_cat_params set 
                    def_value = defValue, 
                    is_mandatory = isMandatory, 
                    is_read_only = isReadOnly, 
                    param_sort_order = acOrder 
                where id_category = idCategory and id_parameter = idParameter;
            end if;

            return idCategoryParam;
        end if;
    end loop;


    idCategoryParam := getNextSeq('tbl_cat_params', 'id');

    insert into tbl_cat_params (id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order)
    values(idCategoryParam, idCategory, idParameter, defValue, isMandatory, isReadOnly, acOrder);

    if(not FOUND) then
        return -1;
    end if;
    
    return idCategoryParam;

end
$BODY$
language 'plpgsql';
