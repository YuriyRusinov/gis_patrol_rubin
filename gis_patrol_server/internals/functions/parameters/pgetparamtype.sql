select f_safe_drop_type('h_get_parameter_type');

create type h_get_parameter_type as (id_param_type int8,
                                     type_name varchar,
                                     type_code varchar);

create or replace function pGetParameterTypes() returns setof h_get_parameter_type as
$BODY$
declare
    r h_get_parameter_type%rowtype;
begin

    for r in
        select id, name, code from tbl_parameter_types
    loop
        return next r;
    end loop;

    return;
end
$BODY$
language 'plpgsql';
