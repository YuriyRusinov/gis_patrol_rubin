create or replace function ioDeleteCheckTable() returns trigger as
$BODY$
declare
    table_name varchar;
    query varchar;
begin

    table_name := old.table_name;
    if (table_name is not null and table_name <> '') then
        if(old.ref_table_name is not null and old.ref_table_name <> '') then
            query = 'select f_safe_drop_table(' || quote_literal(table_name) || ')';
            execute query;
            query = 'select f_safe_drop_table(' || quote_literal('tbl_' || table_name) || ')';
            execute query;
        else
            query = 'select f_safe_drop_table(' || quote_literal(table_name) || ')';
            execute query;
            query = 'select f_safe_drop_table(' || quote_literal('tbl_' || table_name) || ')';
            execute query;
        end if;
        query = 'drop sequence ' || table_name || '_id_seq';
        execute query;
        --raise notice '%', query;
        --execute query;
    end if;
    return old;
end
$BODY$
language 'plpgsql';

select f_safe_drop_trigger('trgiodelete', 'tbl_io_communication_objects_references');

select f_create_trigger('trgiodelete', 'after', 'delete', 'tbl_io_communication_objects_references', 'iodeletechecktable()');

/*
create trigger trgIODelete 
after delete 
on tbl_io_objects 
for each row 
execute procedure ioDeleteCheckTable();
*/
