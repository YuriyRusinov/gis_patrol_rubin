insert into tbl_parameters_groups (id, name) values( 4, 'Атрибуты телекоммуникаций') on conflict do nothing;
--
-- Объекты ИСС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (405, 8, 4, 'iss_object_number', 'Номер объекта', 'Номер объекта', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (406, 9, 4, 'account_iss_object_number', 'Учетный номер объекта', 'Учетный номер объекта', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (407, 2, 4, 'id_iss_object_type', 'Тип объекта', 'Тип объекта', 'tbl_iss_object_type', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (408, 9, 4, 'full_object_name', 'Полное название объекта', 'Полное название объекта', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (409, 9, 4, 'short_object_name', 'Условное название объекта', 'Условное название объекта', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (410, 28, 4, 'control_border', 'Граница объекта ИСС', 'Граница объекта ИСС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (411, 23, 4, 'control_border_pic', 'Граница контрольной зоны', 'Граница контрольной зоны', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (412, 9, 4, 'post_address', 'Почтовый адрес', 'Почтовый адрес', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (413, 2, 4, 'id_iss_adjacent_object1', 'Номера смежных объектов', 'Номера смежных объектов', 'tbl_iss_objects', 'iss_object_number', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (414, 2, 4, 'id_iss_adjacent_object2', 'Номера смежных объектов', 'Номера смежных объектов', 'tbl_iss_objects', 'iss_object_number', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (415, 2, 4, 'id_iss_object', 'Номер объекта ИСС', 'Номера объекта ИСС', 'tbl_iss_objects', 'iss_object_number', false) on conflict do nothing;
--
-- Узлы ИСС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (416, 9, 4, 'node_stat_number', 'Учетный номер узла', 'Учетный номер узла', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (417, 2, 4, 'id_node_type', 'Тип узла', 'Тип узла', 'tbl_iss_node_type', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (418, 9, 4, 'control_management_system', 'Подсистема центрального управления', 'Подсистема центрального управления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (419, 1, 4, 'security_system', 'Система мониторинга информационной безопасности', 'Система мониторинга информационной безопасности', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (420, 9, 4, 'system_management_security', 'Система управления информационной безопасностью', 'Система управления информационной безопасностью', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (421, 8, 4, 'control_level', 'Уровень управления', 'Уровень управления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (422, 8, 4, 'state_number', 'Количество обслуживающего персонала', 'Количество обслуживающего персонала', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (423, 8, 4, 'special_user_category', 'Категория спецпотребителей', 'Категория спецпотребителей', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (424, 28, 4, 'node_border', 'Граница контрольной зоны узла', 'Граница контрольной зоны узла', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (425, 23, 4, 'node_border_pic', 'Граница контрольной зоны узла', 'Граница контрольной зоны узла', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Здания, относящиеся к объекту ИСС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (426, 2, 4, 'id_building_type', 'Тип сооружения', 'Тип сооружения', 'tbl_object_building_type', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (427, 9, 4, 'building_number', 'Учетный номер сооружения', 'Учетный номер сооружения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (428, 9, 4, 'building_name', 'Наименование сооружения', 'Наименование сооружения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (429, 7, 4, 'building_length', 'Размеры сооружения, длина', 'Размеры сооружения, длина', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (430, 7, 4, 'building_width', 'Размеры сооружения, ширина', 'Размеры сооружения, ширина', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (431, 7, 4, 'building_altitude', 'Размеры сооружения, высота', 'Размеры сооружения, высота', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (432, 8, 4, 'number_floors', 'Этажность сооружения', 'Этажность сооружения', null::varchar, null::varchar, false) on conflict do nothing;

--
-- Аттестация узлов
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (433, 2, 4, 'id_iss_node', 'Учетный номер узла ИСС', 'Учетный номер узла ИСС', 'tbl_iss_node', 'node_stat_number', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (434, 4, 4, 'sertification_date', 'Дата аттестации', 'Дата аттестации', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (435, 9, 4, 'agreement_number', 'Номер заключительного соответствия', 'Номер заключительного соответствия', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (436, 2, 4, 'id_sertificate', 'Номер сертификата', 'Номер сертификата', 'tbl_sertificates', 'sertification_number', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (437, 4, 4, 'sertification_valid_date', 'Срок действия сертификата', 'Срок действия сертификата', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (438, 9, 4, 'sertification_number', 'Номер сертификата', 'Номер сертификата', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Категории информационных объектов
--
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (200, 10, null::integer, false, 'Типы телекоммуникационных сущностей', 'TELECOM_CATEGORY_200', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (201, 8, 200, true, 'Справочники типов телекоммуникационных сущностей', 'TELECOM_CATEGORY_201', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (202, 10, null::integer, false, 'Объекты ИСС', 'TELECOM_CATEGORY_202', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (203, 8, 202, true, 'Справочники объектов ИСС', 'TELECOM_CATEGORY_203', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (204, 10, null::integer, false, 'Смежные объекты ИСС', 'TELECOM_CATEGORY_204', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (205, 8, 204, true, 'Справочники смежных объектов ИСС', 'TELECOM_CATEGORY_205', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (206, 10, null::integer, false, 'Узлы ИСС', 'TELECOM_CATEGORY_206', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (207, 8, 206, true, 'Справочники узлов ИСС', 'TELECOM_CATEGORY_207', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (208, 10, null::integer, false, 'Сооружения', 'TELECOM_CATEGORY_208', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (209, 8, 208, true, 'Справочники сооружений', 'TELECOM_CATEGORY_209', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (210, 10, null::integer, false, 'Сертификаты', 'TELECOM_CATEGORY_210', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (211, 8, 210, true, 'Справочники сертификатов', 'TELECOM_CATEGORY_211', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (212, 10, null::integer, false, 'Аттестация узлов', 'TELECOM_CATEGORY_212', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (213, 8, 212, true, 'Справочники аттестатов узлов', 'TELECOM_CATEGORY_213', null::varchar, true) on conflict do nothing;

--
-- Атрибуты категорий
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (601, 200, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (602, 200, 2, null, true, true, 2) on conflict do nothing; -- name

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (603, 202, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (604, 202, 405, null, true, false, 2) on conflict do nothing; -- номер объекта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (605, 202, 406, null, true, false, 3) on conflict do nothing; -- Учетный номер объекта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (606, 202, 407, '1'::varchar, true, false, 4) on conflict do nothing; -- Тип объекта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (607, 202, 408, null::varchar, true, false, 5) on conflict do nothing; -- Полное название объекта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (608, 202, 409, null::varchar, false, false, 6) on conflict do nothing; -- Сокращенное название объекта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (609, 202, 410, null::varchar, false, false, 7) on conflict do nothing; -- Граница объекта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (610, 202, 411, null::varchar, false, false, 8) on conflict do nothing; -- Граница контрольной зоны 
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (611, 202, 412, null::varchar, true, false, 9) on conflict do nothing; -- Почтовый адрес
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (612, 202, 88, null::varchar, false, false, 10) on conflict do nothing; -- Широта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (613, 202, 89, null::varchar, false, false, 11) on conflict do nothing; -- Долгота
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (614, 202, 100, '4326'::varchar, false, false, 12) on conflict do nothing; -- srid

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (615, 204, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (616, 204, 413, null::varchar, true, false, 2) on conflict do nothing; -- id_iss_adjacent_object1
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (617, 204, 414, null::varchar, true, false, 3) on conflict do nothing; -- id_iss_adjacent_object2

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (618, 206, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (619, 206, 416, null::varchar, true, false, 2) on conflict do nothing; -- node_stat_number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (620, 206, 417, null::varchar, true, false, 3) on conflict do nothing; -- node_type
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (621, 206, 415, null::varchar, true, false, 4) on conflict do nothing; -- id_iss_object
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (622, 206, 418, null::varchar, false, false, 5) on conflict do nothing; -- control_management_system
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (623, 206, 419, null::varchar, false, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (624, 206, 420, null::varchar, false, false, 7) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (625, 206, 421, '3'::varchar, true, false, 8) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (626, 206, 422, '0'::varchar, true, false, 9) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (627, 206, 423, null::varchar, false, false, 10) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (628, 206, 424, null::varchar, false, false, 11) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (629, 206, 425, null::varchar, false, false, 12) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (630, 208, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (631, 208, 415, null::varchar, true, false, 2) on conflict do nothing; -- id_building_type
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (632, 208, 426, null::varchar, true, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (633, 208, 427, null::varchar, true, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (634, 208, 428, null::varchar, true, false, 5) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (635, 208, 429, null::varchar, true, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (636, 208, 430, null::varchar, true, false, 7) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (637, 208, 431, null::varchar, true, false, 8) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (638, 208, 432, null::varchar, true, false, 9) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (639, 208, 88, null::varchar, false, false, 10) on conflict do nothing; -- Широта
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (640, 208, 89, null::varchar, false, false, 11) on conflict do nothing; -- Долгота
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (641, 208, 100, '4326'::varchar, false, false, 12) on conflict do nothing; -- srid

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (642, 210, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (643, 210, 438, null::varchar, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (644, 210, 437, null::varchar, true, false, 3) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (645, 212, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (646, 212, 433, null::varchar, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (647, 212, 434, null::varchar, true, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (648, 212, 435, null::varchar, true, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (649, 212, 436, null::varchar, true, false, 5) on conflict do nothing;
--
-- Справочники
--
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (100, 1, 201, 'Справочник типов объектов ИСС', null::varchar, 'tbl_iss_object_type', 'Типы объектов ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (101, 1, 201, 'Справочник типов узлов ИСС', null::varchar, 'tbl_iss_node_type', 'Типы узлов ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (102, 1, 201, 'Справочник типов строений', null::varchar, 'tbl_object_building_type', 'Типы строений', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (103, 1, 203, 'Справочник ИСС объектов', null::varchar, 'tbl_iss_objects', 'Объекты ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (104, 1, 205, 'Справочник смежных объектов', null::varchar, 'tbl_iss_object_adjacent_objects', 'Соседние объекты ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (105, 1, 207, 'Справочник узлов ИСС', null::varchar, 'tbl_iss_node', 'Узлы ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (106, 1, 209, 'Справочник сооружений', null::varchar, 'tbl_object_building', 'Сооружения ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (107, 1, 211, 'Справочник сертификатов', null::varchar, 'tbl_sertificates', 'Сертификаты ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (108, 1, 213, 'Аттестация узлов ИСС', null::varchar, 'tbl_node_sertificates', 'Сертификаты узлов ИСС', false, current_timestamp, true) on conflict do nothing;
--
-- Первоначальные записи справочников
--
insert into tbl_iss_object_type (id, name) values (1, 'Зоновый');
insert into tbl_iss_object_type (id, name) values (2, 'Магистральный');
select setval('tbl_iss_object_type_id_seq', 2, true);

insert into tbl_iss_node_type (id, name) values (1, 'Оконечный');
insert into tbl_iss_node_type (id, name) values (2, 'Транзитный');
select setval('tbl_iss_node_type_id_seq', 2, true);

insert into tbl_object_building_type (id, name) values (1, 'Капитальное');
select setval('tbl_object_building_type_id_seq', 1, true);

alter table tbl_iss_object_adjacent_objects add constraint adjacent_check check (id_iss_adjacent_object1 != id_iss_adjacent_object2);
