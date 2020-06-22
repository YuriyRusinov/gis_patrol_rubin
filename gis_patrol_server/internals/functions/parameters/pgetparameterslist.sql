create or replace function pGetParametersList(int8) returns setof h_get_parameter as
$BODY$
declare
    idParamGroup alias for $1;
    r h_get_parameter%rowtype;
begin
    for r in
        select
            p.id,
            ptt.id,
            p.id_param_group,
            p.code,
            p.name,
            p.title,
            p.table_name,
            p.column_name,
            ptt.name,
            ptt.code,
            null::varchar, -- default_value is possible in categories
            null::boolean,
            null::boolean,
            null::integer
        from
            tbl_parameters p inner join tbl_parameter_types ptt on (p.id_param_type=ptt.id)
            inner join tbl_parameters_groups pg on (p.id_param_group=pg.id and pg.id=idParamGroup) order by 1
        loop
            return next r;
        end loop;

        return;
end
$BODY$
language 'plpgsql';
