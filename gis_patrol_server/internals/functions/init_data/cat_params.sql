--
-- типы категорий
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (1, 3, 1, null, true, true, 1);
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (2, 3, 2, null, true, false, 2);
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (3, 3, 3, null, false, false, 3);
--
-- представления типов параметров
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (4, 5, 1, null, true, true, 1);
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (5, 5, 2, null, true, false, 2);
--
-- типы параметров
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (6, 7, 1, null, true, true, 1);
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (7, 7, 2, null, true, true, 2);
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (8, 7, 6, null, true, true, 3);
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (9, 7, 4, null, true, true, 4);
--
-- параметры
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (10, 9, 1, null, true, true, 1);-- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (11, 9, 5, null, true, true, 2);-- type
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (12, 9, 6, null, true, true, 3);-- code
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (13, 9, 2, null, true, false, 4);-- name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (14, 9, 7, null, true, false, 5);-- title
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (15, 9, 8, null, false, false, 6);-- table_name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (16, 9, 9, null, false, false, 7);-- column_name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (17, 9, 15, null, true, true, 8);-- is_system
--
-- категории
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (18, 11, 1, null, true, true, 1);-- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (19, 11, 10, null, true, false, 2);-- id_category_type
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (20, 11, 11, null, false, false, 3);-- id_child
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (21, 11, 17, null, true, false, 4);-- is_main
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (22, 11, 2, null, true, false, 5);-- name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (23, 11, 6, null, true, false, 6);-- code
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (24, 11, 3, null, false, false, 7);-- description
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (25, 11, 15, null, true, true, 8);-- is_system
--
-- параметры в категориях
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (26, 185, 1, null, true, true, 1);-- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (27, 185, 12, null, true, false, 2);-- id_category
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (28, 185, 303, null, true, false, 3);-- id_parameter
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (29, 185, 304, null, false, false, 4);-- default_value
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (30, 185, 128, 'false', true, false, 5);-- is_mandatory
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (31, 185, 305, 'false', true, false, 6);-- is_read_only
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (32, 185, 404, '1', true, false, 7);-- param_sort_order
--
-- информационные объекты
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (33, 13, 1, null, true, true, 1);-- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (34, 13, 13, null, false, true, 2);-- author
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (35, 13, 12, null, true, true, 3);-- category
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (36, 13, 2, null, true, false, 4);-- name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (37, 13, 3, null, false, false, 5);-- description
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (38, 13, 8, null, false, false, 6);-- table_name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (39, 13, 14, null, false, true, 7);-- information
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (40, 13, 15, 'false', true, true, 8);-- is_system
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (41, 13, 16, 'current_timestamp', true, true, 9);-- insert_time
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (42, 13, 111, 'false', true, false, 10);-- is_global
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (43, 13, 206, null, false, false, 11);-- record_fill_color
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (44, 13, 207, null, false, false, 12);-- record_text_color
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (45, 13, 216, null, false, false, 13);-- ref_table_name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (46, 13, 312, null, false, false, 14);-- r_icon
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (47, 13, 348, null, false, true, 15);-- uuid_t
--
-- грифы секретности
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (48, 45, 1, null, true, true, 1);-- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (49, 45, 2, null, true, true, 2);-- name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (50, 45, 64, null, true, false, 3);-- mac_value
--
-- пользователи
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (51, 49, 1, null, true, true, 1);-- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (52, 49, 63, null, false, false, 2);-- maclabel
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (53, 49, 22, null, true, false, 3);-- firstname
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (54, 49, 23, null, false, false, 3);-- surname
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (55, 49, 24, null, true, false, 4);-- lastname
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (56, 49, 16, 'current_timestamp', true, true, 5);-- insert_time
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (57, 49, 25, null, true, false, 6);-- family_name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (58, 49, 66, null, false, false, 7);-- email
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (59, 49, 26, null, true,false, 8);-- db_user

select setval('tbl_cat_params_id_seq', 1000, true);
