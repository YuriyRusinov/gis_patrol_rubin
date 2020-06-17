create or replace function pUpdateGroup(int8, int8, varchar) returns int8 as
$BODY$
declare
    idGroup alias for $1;
    idParent alias for $2;
    groupName alias for $3;

    idNewGroup int8;

    query varchar;
begin
    select into idNewGroup id from tbl_parameters_groups where id = idGroup;
    if (not found ) then
        return -1;
    end if;

    query := E'update tbl_parameters_groups set id_parent=';
    if (idParent is null) then
        query := query || E'null::int8, ';
    else
        query := query || idParent || E', ';
    end if;
    query := query || E'name=' || quote_literal(groupName) || E' where id=' || idGroup || E' returning id;';
    raise warning '%', query;
    execute query into idNewGroup;

    return idGroup;

    exception when others then
        return -1;
end
$BODY$
language 'plpgsql';
