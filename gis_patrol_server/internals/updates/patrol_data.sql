insert into tbl_parameters_groups (name) values ('Географические атрибуты');  --4

insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (88, 7, 'latitude', 'Широта', 'Широта', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (89, 7, 'longitude', 'Долгота', 'Долгота', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (19, 9, 'short_name', 'Короткое название', 'Короткое название', null::varchar, null::varchar, true);

