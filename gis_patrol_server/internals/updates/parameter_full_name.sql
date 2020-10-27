insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (28, 9, 'full_name', 'Полное название', 'Полное название', null::varchar, null::varchar, true) on conflict do nothing;


