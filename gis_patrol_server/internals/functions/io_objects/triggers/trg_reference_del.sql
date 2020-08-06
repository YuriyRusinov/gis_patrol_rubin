create or replace function ioDeleteCheckRef() returns trigger as
$BODY$
declare
begin
    if( old.is_system or old.id <= 300 ) then
        return null;
    end if;

    return old;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgrefdelete', 'tbl_io_communication_objects_references');

select f_create_trigger('trgrefdelete', 'before', 'delete', 'tbl_io_communication_objects_references', 'iodeletecheckref()');



