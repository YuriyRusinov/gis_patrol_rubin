insert into tbl_parameters_groups (id, name) values( 4, 'Электротехнические атрибуты') on conflict do nothing;
--
-- Объекты ИСС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (410, 28, 4, 'control_border', 'Граница объекта ИСС', 'Граница объекта ИСС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (411, 9, 4, 'post_address', 'Почтовый адрес', 'Почтовый адрес', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (412, 8, 4, 'id_class_object', 'Класс объекта ИСС', 'Класс объекта ИСС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (413, 8, 4, 'id_stat_number', 'Учетный номер узла', 'Учетный номер узла', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (414, 2, 4, 'id_iss_object', 'Объект ИСС', 'Объект ИСС', 'tbl_iss_objects', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (415, 8, 4, 'control_level', 'Уровень управления', 'Уровень управления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (416, 8, 4, 'state_number', 'Численность персонала', 'Численность персонала', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (417, 8, 4, 'special_user_category', 'Категория узла', 'Категория узла', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (418, 28, 4, 'node_border', 'Границы контролируемой зоны узла', 'Границы контролируемой зоны узла', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Здания, относящиеся к объекту ИСС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (419, 7, 4, 'building_length', 'Длина основания', 'Длина основания', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (420, 7, 4, 'building_width', 'Ширина основания', 'Ширина основания', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (421, 7, 4, 'building_altitude', 'Высота строения', 'Высота строения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (422, 8, 4, 'number_floors', 'Количество этажей здания', 'Количество этажей здания', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (423, 2, 4, 'id_building', 'Строение', 'Строение', 'tbl_object_building', 'name', false) on conflict do nothing;
--
-- Помещения в здании
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (424, 8, 4, 'id_floor_room', 'Номер помещения на этаже', 'Номер помещения на этаже', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (425, 8, 4, 'id_floor', 'Номер этажа', 'Номер этажа', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (426, 2, 4, 'id_room', 'Номер помещения', 'Номер помещения', 'tbl_rooms', 'id_floor_number', false) on conflict do nothing;
--
-- Система пожарной сигнализации
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (427, 8, 4, 'id_device', 'Номер устройства', 'Номер устройства', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (428, 9, 4, 'device_model', 'Модель устройства', 'Модель устройства', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (429, 1, 4, 'is_fire', 'Пожарная(true) или охранная(false)', 'Пожарная(true) или охранная(false)', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (430, 9, 4, 'central_control', 'Модель центрального контроллера', 'Модель центрального контроллера', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (431, 9, 4, 'cable_mark', 'Марка кабеля', 'Марка кабеля', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Состояния сигнализации
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (432, 2, 4, 'id_state', 'Состояние ТКО', 'Состояние ТКО', 'tbl_state_tko', 'name', false) on conflict do nothing;
--
-- Система заземления
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (433, 9, 4, 'grounding_bar_mark', 'Маркировка шины заземления', 'Маркировка шины заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (434, 9, 4, 'grounding_cord', 'Марка провода заземления', 'Марка провода заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (435, 7, 4, 'grounding_resistance', 'Сопротивление заземления', 'Сопротивление заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (436, 9, 4, 'grounding_type', 'Тип заземления', 'Тип заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (437, 8, 4, 'grounding_contour_number', 'Номер контура заземления', 'Номер контура заземления', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Система электропитания
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (438, 9, 4, 'serial_number', 'Серийный номер', 'Серийный номер', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (439, 2, 4, 'id_electrical_system', 'Система электропитания', 'Система электропитания', 'tbl_electrical_systems', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (440, 9, 4, 'transformator_mark', 'Модель трансформатора', 'Модель трансформатора', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (441, 9, 4, 'shield_mark', 'Марка электрощита', 'Марка электрощита', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Стационарная часть ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (442, 2, 4, 'id_vols', 'ВОЛС', 'ВОЛС', 'tbl_linear_part_vols', 'color_mark', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (443, 9, 4, 'opt_crosses_purpose', 'Назначение оптических кроссов', 'Назначение оптических кроссов', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (444, 9, 4, 'opt_cross_type', 'Тип оптического кросса', 'Тип оптического кросса', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (445, 8, 4, 'cross_place_number', 'Номер места на оптическом кроссе', 'Номер места на оптическом кроссе', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (446, 8, 4, 'vols_number', 'Номер оптоволокна', 'Номер оптоволокна', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (447, 8, 4, 'column_number', 'Номер шкафа места подключения', 'Номер шкафа места подключения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (448, 8, 4, 'reflection_number', 'Номер рефлектограммы', 'Номер рефлектограммы', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (449, 4, 4, 'date_reflection', 'Дата рефлектограммы', 'Дата рефлектограммы', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (450, 9, 4, 'periturbation_description', 'Описание неоднородностей', 'Описание неоднородностей', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Линейная часть ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (451, 2, 4, 'id_well', 'Номер колодца кабеля сигнализации', 'Номер колодца кабеля сигнализации', 'tbl_well_shaft', 'well_mark', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (452, 18, 4, 'color_mark', 'Маркировка ВОЛС', 'Маркировка ВОЛС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (453, 7, 4, 'vols_length', 'Длина ВОЛС', 'Длина ВОЛС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (454, 8, 4, 'sections_number', 'Количество секций', 'Количество секций', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (455, 7, 4, 'section_length', 'Длина секции', 'Длина секции', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (456, 2, 4, 'id_regenerator', 'Номер регенератора', 'Номер регенератора', 'tbl_regenerator', 'id', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (457, 9, 4, 'vols_type', 'Тип ВОЛС', 'Тип ВОЛС', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Колодец ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (458, 9, 4, 'well_mark', 'Маркировка колодца', 'Маркировка колодца', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Регенератор ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (459, 9, 4, 'regenerator_mark', 'Маркировка регенератора', 'Маркировка регенератора', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (460, 9, 4, 'regenerator_type', 'Тип регенератора', 'Маркировка регенератора', null::varchar, null::varchar, false) on conflict do nothing;
select setval('tbl_parameters_id_seq', 1000, true);

--
-- Категории
--
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (200, 10, null::integer, false, 'Объекты ИСС', 'ELECTRIC_CATEGORY_200', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (201, 8, 200, true, 'Справочник объектов ИСС', 'ELECTRIC_CATEGORY_201', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (202, 10, null::integer, false, 'Узлы ИСС', 'ELECTRIC_CATEGORY_202', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (203, 8, 202, true, 'Справочник узлов ИСС', 'ELECTRIC_CATEGORY_203', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (204, 10, null::integer, false, 'Помещения', 'ELECTRIC_CATEGORY_204', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (205, 8, 204, true, 'Справочник помещений', 'ELECTRIC_CATEGORY_205', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (206, 10, null::integer, false, 'Пожарно-охранная сигнализация', 'ELECTRIC_CATEGORY_206', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (207, 8, 206, true, 'Справочник сигнализаций', 'ELECTRIC_CATEGORY_207', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (208, 10, null::integer, false, 'Состояние сигнализации', 'ELECTRIC_CATEGORY_208', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (209, 8, 208, true, 'Справочник состояний сигнализации', 'ELECTRIC_CATEGORY_209', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (210, 10, null::integer, false, 'Системы заземления', 'ELECTRIC_CATEGORY_210', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (211, 8, 210, true, 'Справочник систем заземления', 'ELECTRIC_CATEGORY_211', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (212, 10, null::integer, false, 'Электросистемы', 'ELECTRIC_CATEGORY_212', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (213, 8, 212, true, 'Справочник электросистем', 'ELECTRIC_CATEGORY_213', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (214, 10, null::integer, false, 'Электрощиты', 'ELECTRIC_CATEGORY_214', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (215, 8, 212, true, 'Справочник электрощитов', 'ELECTRIC_CATEGORY_215', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (216, 10, null::integer, false, 'Электротрансформаторы', 'ELECTRIC_CATEGORY_216', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (217, 8, 216, true, 'Справочник электротрансформаторов', 'ELECTRIC_CATEGORY_217', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (218, 10, null::integer, false, 'ВОЛС, стационарная часть', 'ELECTRIC_CATEGORY_218', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (219, 8, 218, true, 'Справочник стационарных частей ВОЛС', 'ELECTRIC_CATEGORY_219', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (220, 10, null::integer, false, 'ВОЛС, линейная часть', 'ELECTRIC_CATEGORY_220', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (221, 8, 220, true, 'Справочник линейных частей ВОЛС', 'ELECTRIC_CATEGORY_221', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (222, 10, null::integer, false, 'Колодец ВОЛС', 'ELECTRIC_CATEGORY_222', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (223, 8, 222, true, 'Справочник колодцев ВОЛС', 'ELECTRIC_CATEGORY_223', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (224, 10, null::integer, false, 'Регенератор ВОЛС', 'ELECTRIC_CATEGORY_224', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (225, 8, 224, true, 'Справочник регенераторов ВОЛС', 'ELECTRIC_CATEGORY_225', null::varchar, true) on conflict do nothing;

insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (226, 10, null::integer, false, 'Сигнализации', 'ELECTRIC_CATEGORY_226', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (227, 8, 226, true, 'Справочник пожарных и охранных сигнализаций', 'ELECTRIC_CATEGORY_227', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (228, 10, null::integer, false, 'Узлы ИСС (подробно)', 'ELECTRIC_CATEGORY_228', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (229, 8, 228, true, 'Справочник узлов ИСС (подробно)', 'ELECTRIC_CATEGORY_229', null::varchar, true) on conflict do nothing;
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

--
-- здания, относящиеся к узлу
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (609, 202, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (610, 202, 2, null, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (611, 202, 414, null, true, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (612, 202, 419, null, true, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (613, 202, 420, null, true, false, 5) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (614, 202, 421, null, true, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (615, 202, 422, null, true, false, 7) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (616, 202, 89, null, false, false, 8) on conflict do nothing; -- longitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (617, 202, 88, null, false, false, 9) on conflict do nothing; -- latitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (618, 202, 100, null, false, false, 10) on conflict do nothing; -- projection
--
-- Помещения
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (619, 204, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (620, 204, 424, null, true, true, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (621, 204, 425, null, true, true, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (622, 204, 423, null, true, true, 4) on conflict do nothing;
--
-- Пожарно-охранная сигнализация
--
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (623, 206, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (624, 206, 427, null, false, false, 2) on conflict do nothing; -- id_device
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (625, 206, 428, null, true, false, 3) on conflict do nothing; -- device_model
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (626, 206, 426, null, true, false, 4) on conflict do nothing; -- id_room
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (627, 206, 432, null, true, false, 5) on conflict do nothing; -- id_state

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (628, 208, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (629, 208, 2, null, true, false, 2) on conflict do nothing; -- name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (630, 208, 3, null, false, false, 3) on conflict do nothing; -- description

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (631, 210, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (632, 210, 433, null, false, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (633, 210, 434, null, false, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (634, 210, 435, null, false, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (635, 210, 436, null, false, false, 5) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (636, 210, 437, null, false, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (637, 210, 425, null, false, false, 7) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (638, 210, 423, null, false, false, 8) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (639, 212, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (640, 212, 423, null, true, false, 2) on conflict do nothing; -- id_building
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (641, 212, 2, null, true, false, 3) on conflict do nothing; -- name

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (642, 214, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (643, 214, 438, null, true, false, 2) on conflict do nothing; -- serial_number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (644, 214, 441, null, true, false, 3) on conflict do nothing; -- shield_mark
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (645, 214, 439, null, true, false, 4) on conflict do nothing; -- id_electrical_system

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (646, 216, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (647, 216, 438, null, true, false, 2) on conflict do nothing; -- serial_number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (648, 216, 440, null, true, false, 3) on conflict do nothing; -- transformator_mark
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (649, 216, 439, null, true, false, 4) on conflict do nothing; -- id_electrical_system

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (650, 218, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (651, 218, 442, null, true, false, 2) on conflict do nothing; -- id_vols
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (652, 218, 443, null, false, false, 3) on conflict do nothing; -- Назначение оптических кроссов
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (653, 218, 444, null, true, false, 4) on conflict do nothing; -- Тип оптического кросса
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (654, 218, 445, null, false, false, 5) on conflict do nothing; -- Место кросса
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (655, 218, 446, null, true, false, 6) on conflict do nothing; -- Номер оптоволокна
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (656, 218, 447, null, true, false, 7) on conflict do nothing; -- Номер шкафа места подключения
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (657, 218, 448, null, false, false, 8) on conflict do nothing; -- Номер рефлектограммы
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (658, 218, 449, null, false, false, 9) on conflict do nothing; -- Дата рефлектограммы
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (659, 218, 450, null, false, false, 10)  on conflict do nothing; -- Описание неровностей

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (660, 220, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (661, 220, 451, null, true, false, 2) on conflict do nothing; -- id_well
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (662, 220, 453, '0.0', true, false, 3) on conflict do nothing; -- vols_length
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (663, 220, 454, '0', true, false, 4) on conflict do nothing; -- sections_number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (664, 220, 455, '0.0', true, false, 5) on conflict do nothing; -- section_length
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (665, 220, 456, null, true, false, 6) on conflict do nothing; -- id_regenerator
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (666, 220, 457, null, true, false, 7) on conflict do nothing; -- vols_type

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (667, 222, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (668, 222, 458, null, true, false, 2) on conflict do nothing; -- well_mark
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (669, 222, 89, null, true, false, 3) on conflict do nothing; -- longitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (670, 222, 88, null, true, false, 4) on conflict do nothing; -- latitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (671, 222, 90, null, true, false, 5) on conflict do nothing; -- altitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (672, 222, 100, null, true, false, 6) on conflict do nothing; -- srid

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (673, 224, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (674, 224, 459, null, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (675, 224, 460, null, true, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (676, 224, 89, null, true, false, 4) on conflict do nothing; -- longitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (677, 224, 88, null, true, false, 5) on conflict do nothing; -- latitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (678, 224, 90, null, true, false, 6) on conflict do nothing; -- altitude
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (679, 224, 100, null, true, false, 7) on conflict do nothing; -- srid

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (680, 226, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (681, 226, 427, null, true, false, 2) on conflict do nothing; -- id_device
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (682, 226, 428, null, true, false, 3) on conflict do nothing; -- device_model
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (683, 226, 429, 'false', true, false, 4) on conflict do nothing; -- is_fire
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (684, 226, 423, null, true, false, 5) on conflict do nothing; -- id_building
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (685, 226, 430, null, false, false, 6) on conflict do nothing; -- central_control
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (686, 226, 431, null, false, false, 7) on conflict do nothing; -- cable_mark

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (687, 228, 1, null, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (688, 228, 413, null, true, false, 2) on conflict do nothing; -- id_stat_number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (689, 228, 414, null, true, false, 3) on conflict do nothing; -- id_iss_object
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (690, 228, 415, '3', true, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (691, 228, 416, '0', true, false, 5) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (692, 228, 417, '1', true, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (693, 228, 418, null, false, false, 7) on conflict do nothing;
select setval('tbl_cat_params_id_seq', 1000, true);
--
-- Справочники
--
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (100, 1, 201, 'Справочник узлов ИСС', null::varchar, 'tbl_iss_objects', 'Узлы ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (101, 1, 203, 'Справочник строений', null::varchar, 'tbl_object_building', 'Строения узлов ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (102, 1, 205, 'Справочник помещений', null::varchar, 'tbl_rooms', 'Помещения ИСС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (103, 1, 209, 'Справочник состояний сигнализаций', null::varchar, 'tbl_state_tko', 'Состояния сигнализаций', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (104, 1, 207, 'Справочник сигнализаций', null::varchar, 'tbl_fire_alarm_room_device', 'Сигнализации', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (105, 1, 211, 'Справочник систем заземления', null::varchar, 'tbl_fire_alarm_room_device', 'Системы заземления', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (106, 1, 213, 'Справочник систем электропитания', null::varchar, 'tbl_electrical_systems', 'Системы электропитания', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (107, 1, 215, 'Справочник электрощитов', null::varchar, 'tbl_electrical_shield', 'Системы электрощитов', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (108, 1, 223, 'Справочник колодцев ВОЛС', null::varchar, 'tbl_well_shaft', 'Колодцы ВОЛС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (109, 1, 225, 'Справочник регенераторов ВОЛС', null::varchar, 'tbl_regenerator', 'Регенераторы ВОЛС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (110, 1, 217, 'Справочник электротрансформаторов', null::varchar, 'tbl_electrical_transformator', 'Системы электротрансформаторов', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (111, 1, 221, 'Справочник линейных частей ВОЛС', null::varchar, 'tbl_linear_part_vols', 'Линейные части ВОЛС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (112, 1, 219, 'Справочник стационарных частей ВОЛС', null::varchar, 'tbl_stationary_part_vols', 'Стационарные части ВОЛС', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (113, 1, 227, 'Справочник ЦП сигнализаций', null::varchar, 'tbl_fire_security_alarm', 'ЦП сигнализаций', false,  current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (114, 1, 229, 'Справочник Узлов ИСС( подробности )', null::varchar, 'tbl_fire_security_alarm', 'ЦП сигнализаций', false,  current_timestamp, true) on conflict do nothing;
select setval('tbl_communication_objects_references_id_seq', 300, true);
