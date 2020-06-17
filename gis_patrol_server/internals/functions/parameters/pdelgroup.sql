create or replace function pDeleteGroup(int8) returns int8 as
$BODY$
declare
    idParamGroup alias for $1;

    idOldGroup int8;

    cnt integer;
    query varchar;
begin
    select into cnt (select count(*) from tbl_parameters_groups tpg1 inner join tbl_parameters_groups tpg2 on(tpg1.id=tpg2.id_parent and tpg1.id=idParamGroup))+(select count(*) from tbl_parameters p inner join tbl_parameters_groups tpg1 on (p.id_param_group=tpg1.id and tpg1.id=idParamGroup));
    raise warning '%', cnt;
    if (cnt is not null and cnt > 0) then
        raise warning 'Group contains subgroups or parameters, cannot be deleted';
        return -1;
    end if;
    query := E'delete from tbl_parameters_groups where id = ' || idParamGroup || E' returning id';
    execute query into idOldGroup;
    if (not found) then
        return -1;
    end if;

    return idParamGroup;
    exception when others then
        return -1;
end
$BODY$
language 'plpgsql';
