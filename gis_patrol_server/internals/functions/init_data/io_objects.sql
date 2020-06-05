--
-- при первоначальной инициализации нет надобности пересоздания существующих таблиц,
-- поэтому соответствующие триггеры временно отключаются
--
alter table tbl_io_communication_objects_references disable trigger trgioinsert;
alter table tbl_io_communication_objects_references disable trigger zz_trgzioinserttableafter;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (2, 1, 4, 'Справочник типов категорий', null::varchar, 'tbl_category_type', 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (3, 1, 6, 'Справочник типов представлений параметров средств связи', null::varchar, 'tbl_param_views', 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (4, 1, 8, 'Справочник типов параметров', null::varchar, 'tbl_parameter_types', 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (5, 1, 10, 'Справочник параметров', null::varchar, 'tbl_parameters', 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (6, 1, 12, 'Справочник категорий', null::varchar, 'tbl_communication_categories', 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (7, 1, 14, 'Справочник средств коммуникаций', null::varchar, 'tbl_io_communication_objects_references', 'Системный объект', true, current_timestamp, true);
--insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (8, 1, 18, 'Справочник типов средств коммуникации', null::varchar, null::varchar, 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (23, 1, 46, 'Справочник грифов секретности', null::varchar, 'maclabels', 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (25, 1, 50, 'Справочник пользователей', null::varchar, 'users', 'Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (89, 1, 184, 'Справочник значений атрибутов в информационных объектах', null::varchar, 'tbl_cat_params','Системный объект', true, current_timestamp, true);
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (90, 1, 186, 'Справочник параметров в категориях', null::varchar, 'tbl_cat_params', 'Системный объект', true, current_timestamp, true);
select setval('tbl_communication_objects_references_id_seq', 300, true); --все пользовательские информационные объекты будут начинаться с номера 301
alter table tbl_io_communication_objects_references enable trigger trgioinsert;
alter table tbl_io_communication_objects_references enable trigger zz_trgzioinserttableafter;
