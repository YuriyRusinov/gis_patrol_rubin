create or replace function pUpdate(int4, int4, int4, varchar, varchar, varchar, varchar, varchar) returns int4 as
$BODY$
declare
    idParameter alias for $1;
    idParamType alias for $2;
    idParamGroup alias for $3;
    parameter_code alias for $4;
    parameter_name alias for $5;
    parameter_title alias for $6;
    parameter_table_name alias for $7;
    parameter_column_name alias for $8;

    ptype int4;
    pcode varchar;
    r record;
begin

    for r in
        select p.id_param_type, p.code
        from
            tbl_parameters p
        where
            p.id = idParameter
    loop
        ptype := r.id_param_type;
        pcode := r.code;
    end loop;
    if (ptype is not null and idParamType != ptype) then
        raise exception 'Cannot change parameter type';
        return -1;
    end if;

    if (pcode is not null and lower(parameter_code) != lower(pcode)) then
        raise exception 'Cannot change parameter code';
        return -1;
    end if;

    update tbl_parameters set
        id_param_group = idParamGroup,
        name = parameter_name,
        title = parameter_title,
        table_name = parameter_table_name,
        column_name = parameter_column_name
        where
            id = idParameter;

    if (not FOUND) then
        return -1;
    end if;
    return idParameter;
end
$BODY$
language 'plpgsql';
