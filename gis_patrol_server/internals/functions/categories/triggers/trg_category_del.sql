create or replace function categorydelcheck() returns trigger as
$BODY$
declare
begin
    if( old.is_system or old.id_category_type = 8 ) then
        return null;
    end if;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgcatdel', 'tbl_communication_categories');

select f_create_trigger('trgcatdel', 'before', 'delete', 'tbl_communication_categories', 'categorydelcheck()');
