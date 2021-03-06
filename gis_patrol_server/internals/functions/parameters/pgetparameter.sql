select f_safe_drop_type('h_get_parameter');

create type h_get_parameter as (id_parameter int8,
                                id_param_type int8,
                                id_param_group int8,
                                parameter_code varchar,
                                parameter_name varchar,
                                parameter_title varchar,
                                table_name varchar,
                                column_name varchar,
                                parameter_type_name varchar,
                                parameter_type_code varchar,
                                default_value varchar,
                                is_mandatory boolean,
                                is_read_only boolean,
                                param_sort_order integer,
                                id_ex int8,
                                id_param_ref int8,
                                ref_type_id int8,
                                ref_type_name varchar,
                                ref_type_code varchar
                            );

create or replace function pGetParameter(int8) returns setof h_get_parameter as
$BODY$
declare
    idParameter alias for $1;
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
            null::integer,
            null::int8,
            p1.id,
            ptt1.id,
            ptt1.name,
            ptt1.code
        from
            tbl_parameters p inner join tbl_parameter_types ptt on (p.id_param_type=ptt.id and p.id=idParameter) left join tbl_parameters p1 on (p.column_name=p1.code and p.column_name is not null) left join tbl_parameter_types ptt1 on (p1.id_param_type=ptt1.id)
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function pGetParameter(varchar) returns setof h_get_parameter as
$BODY$
declare
    parameter_code alias for $1;
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
            null::integer,
            null::int8,
            p1.id,
            ptt1.id,
            ptt1.name,
            ptt1.code
        from
            tbl_parameters p inner join tbl_parameter_types ptt on (p.id_param_type=ptt.id and lower(p.code)=lower(parameter_code)) left join tbl_parameters p1 on (p.column_name=p1.code and p.column_name is not null) left join tbl_parameter_types ptt1 on (p1.id_param_type=ptt1.id)
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';
