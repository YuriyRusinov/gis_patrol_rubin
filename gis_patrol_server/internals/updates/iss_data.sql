insert into tbl_parameters_groups (id, name) values( 4, 'Электротехнические атрибуты') on conflict do nothing;

insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (410, 28, 4, 'control_border', 'Граница объекта ИСС', 'Граница объекта ИСС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (411, 9, 4, 'post_address', 'Почтовый адрес', 'Почтовый адрес', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (412, 8, 4, 'id_class_object', 'Класс объекта ИСС', 'Класс объекта ИСС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (413, 8, 4, 'id_stat_number', 'Учетный номер узла', 'Учетный номер узла', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (414, 2, 4, 'id_iss_object', 'Объект ИСС', 'Объект ИСС', 'tbl_iss_objects', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (415, 8, 4, 'control_level', 'Уровень управления', 'Уровень управления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (416, 8, 4, 'state_number', 'Численность персонала', 'Численность персонала', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (417, 8, 4, 'special_user_category', 'Категория узла', 'Категория узла', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (418, 28, 4, 'node_border', 'Границы контролируемой зоны узла', 'Границы контролируемой зоны узла', null::varchar, null::varchar, false) on conflict do nothing;


select setval('tbl_parameters_id_seq', 1000, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (200, 10, null::integer, false, 'Объекты ИСС', 'ELECTRIC_CATEGORY_200', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (201, 8, 200, true, 'Справочник объектов ИСС', 'ELECTRIC_CATEGORY_201', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (202, 10, null::integer, false, 'Узлы ИСС', 'ELECTRIC_CATEGORY_202', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (203, 8, 202, true, 'Справочник узлов ИСС', 'ELECTRIC_CATEGORY_203', null::varchar, true) on conflict do nothing;


select setval('tbl_communication_categories_id_seq', 500, true);
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (601, 200, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (602, 200, 412, null, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (603, 200, 2, null, true, false, 3) on conflict do nothing; -- name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (603, 200, 19, null, true, false, 3) on conflict do nothing; -- short name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (604, 200, 410, null, false, false, 4) on conflict do nothing; -- border
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (605, 200, 411, null, true, false, 5) on conflict do nothing; -- post address
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (606, 200, 89, null, false, false, 6) on conflict do nothing; -- longitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (607, 200, 88, null, false, false, 7) on conflict do nothing; -- latitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (608, 200, 100, null, false, false, 8) on conflict do nothing; -- projection

select setval('tbl_cat_params_id_seq', 1000, true);

insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (100, 1, 201, 'Справочник узлов ИСС', null::varchar, 'tbl_iss_objects', 'Узлы ИСС', false, current_timestamp, true) on conflict do nothing;
select setval('tbl_communication_objects_references_id_seq', 300, true);
