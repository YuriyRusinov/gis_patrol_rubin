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
-- Состав ПО
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (439, 2, 4, 'id_soft', 'Состав пакета ПО', 'Состав пакета ПО', 'tbl_node_soft', 'software_list', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (440, 9, 4, 'software_list', 'Состав пакета ПО', 'Состав пакета ПО', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (441, 9, 4, 'software_version', 'Версия пакета ПО', 'Версия пакета ПО', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (442, 9, 4, 'software_crc', 'Контрольные суммы пакета ПО', 'Контрольные суммы пакета ПО', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Security
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (443, 8, 4, 'confidential_levels', 'Атрибуты политик безопасности', 'Атрибуты политик безопасности', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Помещения в здании
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (444, 8, 4, 'id_floor_room', 'Номер помещения на этаже', 'Номер помещения на этаже', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (445, 8, 4, 'id_floor', 'Номер этажа', 'Номер этажа', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (446, 2, 4, 'id_room', 'Номер помещения', 'Номер помещения', 'tbl_rooms', 'id_floor_number', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (447, 7, 4, 'room_length', 'Размер помещения, длина', 'Размер помещения, длина', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (448, 7, 4, 'room_width', 'Размер помещения, ширина', 'Размер помещения, ширина', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (449, 9, 4, 'room_name', 'Наименование помещения', 'Наименование помещения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (450, 2, 4, 'id_building', 'Номер сооружения', 'Номер сооружения', 'tbl_object_building', 'building_number', false) on conflict do nothing;
--
-- Системы пожарной и охранной сигнализации
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (451, 8, 4, 'id_device', 'Номер устройства', 'Номер устройства', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (452, 9, 4, 'device_model', 'Модель устройства', 'Модель устройства', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (453, 1, 4, 'is_fire', 'Пожарная(true) или охранная(false)', 'Пожарная(true) или охранная(false)', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (454, 9, 4, 'central_control', 'Модель центрального контроллера', 'Модель центрального контроллера', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (455, 9, 4, 'cable_mark', 'Марка кабеля', 'Марка кабеля', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Состояния сигнализации
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (456, 2, 4, 'id_state', 'Состояние ТКО', 'Состояние ТКО', 'tbl_state_tce', 'name', false) on conflict do nothing;
--
-- Система заземления
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (457, 9, 4, 'grounding_bar_mark', 'Маркировка шины заземления', 'Маркировка шины заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (458, 9, 4, 'grounding_cord', 'Марка провода заземления', 'Марка провода заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (459, 7, 4, 'grounding_resistance', 'Сопротивление заземления', 'Сопротивление заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (460, 9, 4, 'grounding_type', 'Тип заземления', 'Тип заземления', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (461, 8, 4, 'grounding_contour_number', 'Номер контура заземления', 'Номер контура заземления', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Система электропитания
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (462, 9, 4, 'electrical_serial_number', 'Серийный номер', 'Серийный номер', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (463, 2, 4, 'id_electrical_system', 'Система электропитания', 'Система электропитания', 'tbl_electrical_systems', 'name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (464, 9, 4, 'transformator_mark', 'Модель трансформатора', 'Модель трансформатора', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (465, 9, 4, 'shield_mark', 'Марка электрощита', 'Марка электрощита', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Стационарная часть ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (466, 2, 4, 'id_vols', 'ВОЛС', 'ВОЛС', 'tbl_linear_part_vols', 'color_mark', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (467, 9, 4, 'opt_crosses_purpose', 'Назначение оптических кроссов', 'Назначение оптических кроссов', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (468, 9, 4, 'opt_cross_type', 'Тип оптического кросса', 'Тип оптического кросса', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (469, 8, 4, 'cross_place_number', 'Номер места на оптическом кроссе', 'Номер места на оптическом кроссе', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (470, 8, 4, 'vols_number', 'Номер оптоволокна', 'Номер оптоволокна', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (471, 8, 4, 'column_number', 'Номер шкафа места подключения', 'Номер шкафа места подключения', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (472, 8, 4, 'reflection_number', 'Номер рефлектограммы', 'Номер рефлектограммы', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (473, 4, 4, 'date_reflection', 'Дата рефлектограммы', 'Дата рефлектограммы', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (474, 9, 4, 'periturbation_description', 'Описание неоднородностей', 'Описание неоднородностей', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Линейная часть ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (475, 2, 4, 'id_well', 'Номер колодца кабеля сигнализации', 'Номер колодца кабеля сигнализации', 'tbl_well_shaft', 'well_mark', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (476, 18, 4, 'color_mark', 'Маркировка ВОЛС', 'Маркировка ВОЛС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (477, 7, 4, 'vols_length', 'Длина ВОЛС', 'Длина ВОЛС', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (478, 8, 4, 'sections_number', 'Количество секций', 'Количество секций', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (479, 7, 4, 'section_length', 'Длина секции', 'Длина секции', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (480, 2, 4, 'id_regenerator', 'Номер регенератора', 'Номер регенератора', 'tbl_regenerator', 'id', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (481, 9, 4, 'vols_type', 'Тип ВОЛС', 'Тип ВОЛС', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Колодец ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (482, 9, 4, 'well_mark', 'Маркировка колодца', 'Маркировка колодца', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Регенератор ВОЛС
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (483, 9, 4, 'regenerator_mark', 'Маркировка регенератора', 'Маркировка регенератора', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (484, 9, 4, 'regenerator_type', 'Тип регенератора', 'Маркировка регенератора', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Оборудование Телеком и его размещение
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (485, 9, 4, 'equipment_name', 'Наименование ТКО', 'Наименование ТКО', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (486, 8, 4, 'serial_number', 'Заводской номер', 'Заводской номер', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (487, 9, 4, 'solid_equipment', 'Состав ЗИП', 'Состав ЗИП', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (488, 9, 4, 'solid_equipment_type', 'Тип ЗИП', 'Тип ЗИП', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (489, 13, 4, 'equipment_purpose', 'Назначение модуля ТКО', 'Назначение модуля ТКО', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (490, 2, 4, 'id_equipment_module', 'Номер модуля ТКО', 'Номер модуля ТКО', 'tbl_telecom_equipment', 'equipment_name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (491, 8, 4, 'id_board', 'Номер шкафа', 'Номер шкафа', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (492, 8, 4, 'id_shelf', 'Номер полки в шкафу', 'Номер полки в шкафу', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (493, 8, 4, 'id_board_place', 'Номер места модуля в шкафу', 'Номер места модуля в шкафу', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (494, 8, 4, 'id_basket', 'Номер места модуля в корзине', 'Номер места модуля в корзине', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (495, 8, 4, 'serial_number_minor', 'Номер версии', 'Номер версии', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (496, 8, 4, 'serial_number_minor_minor', 'Номер версии (patch)', 'Номер версии (patch)', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (497, 4, 4, 'date_of_production', 'Дата производства', 'Дата производства', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (498, 4, 4, 'date_of_entry', 'Дата ввода в эксплуатацию', 'Дата ввода в эксплуатацию', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Системы кондиционирования, вентиляции и отопления
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (499, 23, 4, 'heating', 'Система отопления на этаже', 'Система отопления на этаже', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (500, 23, 4, 'conditioning', 'Система кондиционирования на этаже', 'Система кондиционирования на этаже', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (501, 23, 4, 'venting', 'Система вентиляции на этаже', 'Система вентиляции на этаже', null::varchar, null::varchar, false) on conflict do nothing;
--
-- Размещение модулей и субмодулей
--
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (502, 2, 4, 'id_module', 'Номер модуля', 'Номер модуля', 'tbl_telecom_equipment', 'equipment_name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (503, 2, 4, 'id_submodule', 'Номер субмодуля', 'Номер субмодуля', 'tbl_telecom_submodules', 'submodule_name', false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (504, 9, 4, 'submodule_name', 'Наименование субмодуля', 'Наименование субмодуля', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (505, 13, 4, 'submodule_purpose', 'Назначение субмодуля ТКО', 'Назначение субмодуля ТКО', null::varchar, null::varchar, false) on conflict do nothing;
insert into tbl_parameters(id, id_param_type, id_param_group, code, name, title, table_name, column_name, is_system) values (506, 8, 4, 'place_number', 'Номер места', 'Номер места', null::varchar, null::varchar, false) on conflict do nothing;
select setval('tbl_parameters_id_seq', 600, true);

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
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (214, 10, null::integer, false, 'Состав пакетов ПО', 'TELECOM_CATEGORY_214', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (215, 8, 214, true, 'Справочники ПО', 'TELECOM_CATEGORY_215', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (216, 10, null::integer, false, 'Состав пакетов ПО на узлах', 'TELECOM_CATEGORY_216', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (217, 8, 216, true, 'Справочники ПО по узлам', 'TELECOM_CATEGORY_217', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (218, 10, null::integer, false, 'Атрибуты политик безопасности', 'TELECOM_CATEGORY_218', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (219, 8, 218, true, 'Справочники атрибутов политик безопасности', 'TELECOM_CATEGORY_219', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (220, 10, null::integer, false, 'Помещения сооружений', 'TELECOM_CATEGORY_220', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (221, 8, 220, true, 'Справочники помещений', 'TELECOM_CATEGORY_221', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (222, 10, null::integer, false, 'Пожарно-охранная сигнализация', 'TELECOM_CATEGORY_222', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (223, 8, 222, true, 'Справочник сигнализаций', 'TELECOM_CATEGORY_223', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (224, 10, null::integer, false, 'Состояние оборудования', 'TELECOM_CATEGORY_224', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (225, 8, 224, true, 'Справочник состояний ТКО', 'TELECOM_CATEGORY_225', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (226, 10, null::integer, false, 'Оборудование ТКО', 'TELECOM_CATEGORY_226', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (227, 8, 226, true, 'Справочник оборудования ТКО', 'TELECOM_CATEGORY_227', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (228, 10, null::integer, false, 'Системы заземления', 'TELECOM_CATEGORY_228', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (229, 8, 228, true, 'Справочник систем заземления', 'TELECOM_CATEGORY_229', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (230, 10, null::integer, false, 'Системы электропитания', 'TELECOM_CATEGORY_230', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (231, 8, 230, true, 'Справочник систем электропитания', 'TELECOM_CATEGORY_231', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (232, 10, null::integer, false, 'Электрощиты', 'TELECOM_CATEGORY_232', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (233, 8, 232, true, 'Справочник электрощитов', 'TELECOM_CATEGORY_233', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (234, 10, null::integer, false, 'Электротрансформаторы', 'TELECOM_CATEGORY_234', null::varchar, true) on conflict do nothing;
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (235, 8, 234, true, 'Справочник электротрансформаторов', 'TELECOM_CATEGORY_235', null::varchar, true) on conflict do nothing;


--
-- Атрибуты категорий
--
select setval('tbl_cat_params_id_seq', 600, true);
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

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (650, 214, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (651, 214, 440, null::varchar, true, false, 2) on conflict do nothing; --software_list
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (652, 214, 441, null::varchar, true, false, 3) on conflict do nothing; -- software_version
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (653, 214, 442, null::varchar, true, false, 4) on conflict do nothing; -- software_crc

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (654, 216, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (655, 216, 433, null::varchar, true, false, 2) on conflict do nothing; -- id_iss_node
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (656, 216, 439, null::varchar, true, false, 3) on conflict do nothing; -- id_soft

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (657, 218, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (658, 218, 433, null::varchar, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (659, 218, 443, null::varchar, true, false, 3) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (660, 220, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (661, 220, 450, null::varchar, true, false, 2) on conflict do nothing; -- id_building
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (662, 220, 444, null::varchar, true, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (663, 220, 445, null::varchar, true, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (664, 220, 447, null::varchar, false, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (665, 220, 448, null::varchar, false, false, 7) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (666, 220, 449, null::varchar, false, false, 5) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (667, 222, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (668, 222, 451, null::varchar, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (669, 222, 452, null::varchar, true, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (670, 222, 453, 'true'::varchar, true, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (671, 222, 426, null::varchar, true, false, 5) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (672, 222, 454, null::varchar, false, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (673, 222, 455, null::varchar, false, false, 7) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (674, 224, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (675, 224, 2, null::varchar, true, false, 2) on conflict do nothing; -- name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (676, 224, 3, null::varchar, false, false, 3) on conflict do nothing; -- description

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (677, 226, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (678, 226, 485, null::varchar, false, false, 2) on conflict do nothing; -- equipment_name
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (679, 226, 486, null::varchar, true, false, 3) on conflict do nothing; -- serial_number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (680, 226, 495, null::varchar, false, false, 4) on conflict do nothing; -- serial_number_minor
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (681, 226, 496, null::varchar, false, false, 5) on conflict do nothing; -- serial_number_patch
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (682, 226, 497, null::varchar, true, false, 6) on conflict do nothing; -- date_of_production
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (683, 226, 498, null::varchar, true, false, 7) on conflict do nothing; -- date_of_entry
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (684, 226, 456, null::varchar, true, false, 8) on conflict do nothing; -- id_state
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (685, 226, 487, null::varchar, false, false, 9) on conflict do nothing; -- solid_equipment
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (686, 226, 488, null::varchar, false, false, 10) on conflict do nothing; -- solid_equipment_type
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (687, 226, 489, null::varchar, false, false, 11) on conflict do nothing; -- equipment_purpose

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (688, 228, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (689, 228, 457, null::varchar, false, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (690, 228, 458, null::varchar, false, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (691, 228, 459, null::varchar, false, false, 4) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (692, 228, 460, null::varchar, false, false, 5) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (693, 228, 461, null::varchar, false, false, 6) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (694, 228, 445, null::varchar, false, false, 7) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (695, 228, 450, null::varchar, false, false, 8) on conflict do nothing;

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (696, 230, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (697, 230, 450, null, true, false, 2) on conflict do nothing; -- id_building
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (698, 230, 2, null, true, false, 3) on conflict do nothing; -- name

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (699, 232, 1, null::varchar, true, true, 1) on conflict do nothing; -- id
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (700, 232, 462, null, true, false, 2) on conflict do nothing; -- electrical shield serial number
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (701, 232, 465, null, true, false, 3) on conflict do nothing; -- electrical shield mark
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (702, 232, 463, null, true, false, 4) on conflict do nothing; -- electrical system

insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (703, 234, 1, null, true, true, 1) on conflict do nothing; -- id 
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (704, 234, 462, null, true, false, 2) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (705, 234, 464, null, false, false, 3) on conflict do nothing;
insert into tbl_cat_params(id, id_category, id_parameter, default_value, is_mandatory, is_read_only, param_sort_order) values (706, 234, 463, null, true, false, 4) on conflict do nothing;


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
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (109, 1, 215, 'Справочники ПО', null::varchar, 'tbl_software', 'Справочники ПО', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (110, 1, 217, 'Справочники ПО на узлах ИСС', null::varchar, 'tbl_node_soft', 'Справочники ПО по узлам', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (111, 1, 219, 'Справочник политик безопасности', null::varchar, 'tbl_node_security', 'Атрибуты политик безопасности', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (112, 1, 221, 'Справочник помещений', null::varchar, 'tbl_rooms', 'Помещения', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (113, 1, 223, 'Справочник сигнализаций', null::varchar, 'tbl_fire_security_alarm', 'Пожарная или охранная сигнализация', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (114, 1, 225, 'Справочник состояний ТКО', null::varchar, 'tbl_state_tce', 'Состояния ТКО', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (115, 1, 227, 'Справочник ТКО', null::varchar, 'tbl_telecom_equipment', 'Телекоммуникационное оборудование', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (116, 1, 229, 'Справочник систем заземления', null::varchar, 'tbl_grounding_system', 'Система заземления', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (117, 1, 231, 'Справочник систем электропитания', null::varchar, 'tbl_electrical_systems', 'Системы электропитания', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (118, 1, 233, 'Справочник электрощитов', null::varchar, 'tbl_electrical_shield', 'Электрощиты', false, current_timestamp, true) on conflict do nothing;
insert into tbl_io_communication_objects_references (id, id_author, id_category, name, description, table_name, information, is_system, insert_time, is_global) values (119, 1, 235, 'Справочник электротрансформаторов', null::varchar, 'tbl_electrical_transformator', 'Электротрансформаторы', false, current_timestamp, true) on conflict do nothing;
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
