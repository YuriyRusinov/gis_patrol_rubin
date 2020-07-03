create or replace function paramdelcheck() returns trigger as
$BODY$
declare
begin

    if(old.is_system is not null and old.is_system) then
        return null;
    end if;

    return old;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgparamdel', 'tbl_parameters');

select f_create_trigger('trgparamdel', 'before', 'delete', 'tbl_parameters', 'paramdelcheck()');
