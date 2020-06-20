create or replace function paramgroupcheck() returns trigger as
$BODY$
declare
    id_new_parent int8;
    id_old_parent int8;
    query varchar;
    cnt int8;
begin

    if(TG_OP = 'UPDATE') then
        if(old.id_parent is not null and new.id_parent is not null and new.id_parent != old.id_parent) then
            return null;
        else 
            if (old.id_parent is null and new.id_parent is not null) then
                query := E'select count(*) from tbl_parameters_groups tpg inner join tbl_parameters_groups tpg1 on (tpg1.id_parent=tpg.id and tpg1.id=tpg.id_parent and tpg1.id_parent=' || new.id_parent || E');';
                raise warning 'query is %', query;
                execute query into cnt;
                raise warning 'cnt is %', cnt;
                if (cnt > 0) then
                    raise exception 'Attempt to cycle parent and child groups';
                    return null;
                end if;
            end if;
        end if;
    end if;

    return new;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgparamgroup', 'tbl_parameters_groups');

select f_create_trigger('trgparamgroup', 'after', 'insert or update', 'tbl_parameters_groups', 'paramgroupcheck()');
