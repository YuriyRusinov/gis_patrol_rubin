create or replace function pInsertGroup(int8, varchar) returns int8 as
$BODY$
declare
    idParent alias for $1;
    groupName alias for $2;

    query varchar;
    idParamGroup int8;
begin
    select getNextSeq('tbl_parameters_groups', 'id') into idParamGroup;
    query := E'insert into tbl_parameters_groups (id, id_parent, name) values (' || idParamGroup || E',';
    if (idParent is null) then
        query := query || E' null::integer, ';
    else
        query := query || E' ' || idParent || E', ';
    end if;
    query := query || quote_literal(groupName) || E');';
    raise warning '%', query;
    execute query;

    if (not FOUND) then
        return -1;
    end if;

    return idParamGroup;
    exception when others then
        return -1;
end
$BODY$
language 'plpgsql';
