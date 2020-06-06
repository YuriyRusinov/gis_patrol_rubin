create or replace function pFindEqual(int4, varchar, varchar, varchar, varchar, varchar) returns int4 as
$BODY$
declare
    idParamType alias for $1;
    parameter_code alias for $2;
    parameter_name alias for $3;
    parameter_title alias for $4;
    parameter_table_name alias for $5;
    parameter_column_name alias for $6;

    idParameter int4;
    r RECORD;
begin

    for r in
        select id
        from tbl_parameters p
        where
            p.id_param_type = idParamType
            and p.code = parameter_code
            and p.name = parameter_name
            and p.title = parameter_title
            and (case when parameter_table_name is not null then p.table_name =parameter_table_name else p.table_name is null end)
            and (case when parameter_column_name is not null then p.column_name = parameter_column_name else p.column_name is null end)
        order by id
    loop
        return r.id;
    end loop;

    return -1;
end
$BODY$
language 'plpgsql';
