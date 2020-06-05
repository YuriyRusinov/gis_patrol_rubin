--
-- триггер проверяет существование информационных объектов в категории, в которую добавляется
-- параметр, если таковые существуют, то добавление или обновление параметра должно быть пресечено
--  
create or replace function catParamInsertCheck() returns trigger as
$BODY$
declare
    id_category integer;
    cnt integer;
    r record;
begin
    select into cnt count(*) from tbl_io_communication_objects_references io inner join tbl_communication_categories c on (io.id_category=c.id and (c.id=new.id_category or c.id_child=new.id_category));
    if (cnt is not null and cnt > 0) then
        raise exception 'Cannot add parameter into existing objects';
        return null;
    end if;

    return new;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgcatparaminsert', 'tbl_cat_params');

select f_create_trigger('trgcatparaminsert', 'before', 'insert or update', 'tbl_cat_params', 'catParamInsertCheck()');
