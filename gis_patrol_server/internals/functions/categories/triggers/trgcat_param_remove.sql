--
-- триггер проверяет существование информационных объектов в категории, из которой добавляется
-- параметр, если таковые существуют, то удаление параметра должно быть пресечено
--  
create or replace function catParamRemoveCheck() returns trigger as
$BODY$
declare
    id_category integer;
    cnt integer;
    r record;
begin
    select into cnt count(*) from tbl_io_communication_objects_references io inner join tbl_communication_categories c on (io.id_category=c.id and (c.id=old.id_category or c.id_child=old.id_category));
    if (cnt is not null and cnt > 0) then
        raise exception 'Cannot remove parameter into existing objects';
        return null;
    end if;

    return old;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgcatparamdelete', 'tbl_cat_params');

select f_create_trigger('trgcatparamdelete', 'before', 'delete', 'tbl_cat_params', 'catParamRemoveCheck()');
