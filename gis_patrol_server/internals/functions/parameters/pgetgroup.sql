select f_safe_drop_type('h_get_parameter_group');

create type h_get_parameter_group as (id_param_group int8,
                                      id_parent int8,
                                      name varchar);

create or replace function pGetParamGroup(int8) returns setof h_get_parameter_group as
$BODY$
declare
    idParamGroup alias for $1;

    rec h_get_parameter_group%rowtype;
begin

    for rec in
        select pg.id,
               pg.id_parent,
               pg.name
           from tbl_parameters_groups pg
           where pg.id = idParamGroup
    loop
        return next rec;
    end loop;

    return;
end
$BODY$
language 'plpgsql';

create or replace function pGetParamGroups(int8) returns setof h_get_parameter_group as
$BODY$
declare
    idParamParentGroup alias for $1;

    query varchar;
    rec h_get_parameter_group%rowtype;
    rrec h_get_parameter_group%rowtype;
begin
    query := E'select pg.id, pg.id_parent, pg.name from tbl_parameters_groups pg where pg.id_parent ';
    if (idParamParentGroup is null) then
        query := query || E' is null';
    else
        query := query || E' = ' || idParamParentGroup;
    end if;

    for rec in
        execute query
    loop
        return next rec;
        for rrec in
            select * from pGetParamGroups(rec.id_param_group)
        loop
            return next rrec;
        end loop;
    end loop;
    return;
end
$BODY$
language 'plpgsql';
