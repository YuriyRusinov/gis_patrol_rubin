alter table tbl_cat_params disable trigger trgcatparaminsert; 
--таблица значений атрибутов в информационных объектах
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (501, 183, 1, null, true, true, 1); -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (502, 183, 3, null, false, false, 2); -- description
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (503, 183, 48, null, true, false, 3); -- id_communication_object
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (504, 183, 300, null, true, false, 4);--id_param_category
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (505, 183, 301, null, true, false, 5);-- value
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (506, 183, 297, 'current_timestamp', true, false, 6); --start_time
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (507, 183, 298, null, false, false, 7);-- finish_time
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (508, 183, 16, 'current_timestamp', true, false, 8);-- insert_time
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (509, 183, 302, 'true', true, true, 9);

alter table tbl_parameter_values add column if not exists insert_time timestamptz not null default current_timestamp;
alter table tbl_parameter_values rename column id_cat_param to id_param_category;
alter table tbl_cat_params enable trigger trgcatparaminsert;
