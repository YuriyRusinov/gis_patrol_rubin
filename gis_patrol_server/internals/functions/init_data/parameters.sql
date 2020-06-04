insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (1, 30, 'id', 'Идентификатор', 'ИД', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (2, 9, 'name', 'Название', 'Название', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (3, 9, 'description', 'Описание', 'Описание', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (4, 2, 'id_param_view', 'Визуальный элемент управления', 'Виджет', 'tbl_param_views', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (5, 2, 'id_param_type', 'Тип параметра', 'Тип параметра', 'tbl_parameter_types', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (6, 9, 'code', 'Код', 'Код', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (7, 9, 'title', 'Визуальная надпись', 'Надпись', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (8, 9, 'table_name', 'Название таблицы', 'Название таблицы', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (9, 9, 'column_name', 'Название колонки таблицы', 'Колонка таблицы', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (10, 2, 'id_category_type', 'Тип категории объекта средств связи', 'Тип категории', 'tbl_category_type', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (11, 3, 'id_child', 'Подчиненная категория', 'Подчиненная категория', 'tbl_communication_categories', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (12, 2, 'id_category', 'Категория объекта средств связи', 'Категория', 'tbl_communication_categories', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (13, 2, 'id_author', 'Автор (создатель)', 'Автор', 'users', 'family_name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (14, 13, 'information', 'Информация об авторе', 'Информация об авторе', 'users', 'information', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (15, 1, 'is_system', 'Системный', 'Системный', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (16, 6, 'insert_time', 'Дата и время создания', 'Создан( внесен в БД)', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (17, 1, 'is_main', 'Основная категория', 'Основная категория', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (21, 9, 'role_name', 'Системный пользователь', 'Системный пользователь', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (22, 9, 'firstname', 'Имя', 'Имя', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (23, 9, 'surname', 'Отчество', 'Отчество', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (24, 9, 'lastname', 'Фамилия', 'Фамилия', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (25, 9, 'family_name', 'Фамилия, инициалы', 'Фамилия, инициалы', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (26, 9, 'db_user', 'Пользователь БД', 'Пользователь БД', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (27, 3, 'id_parent', 'Родитель', 'Входит в', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (32, 2, 'id_user', 'Пользователь', 'Пользователь', 'users', 'family_name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (48, 2, 'id_communication_object', 'Ресурс связи', 'Ресурс', 'tbl_io_communication_objects_references', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (63, 2, 'id_maclabel', 'Гриф секретности', 'Гриф секретности', 'maclabels', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (64, 9, 'mac_value', 'Мандатная метка', 'Мандатная метка', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (66, 9, 'email', 'Адрес эл. почты', 'Адрес электронной почты', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (111, 1, 'is_global', 'Является глобальным', 'Глобальный', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (128, 1, 'is_mandatory', 'Является обязательным', 'Является обязательным', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (206, 18, 'record_fill_color', 'Цвет фона при отображении в таблице', 'Цвет фона при отображении в таблице', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (207, 25, 'record_text_color', 'Цвет текста при отображении в таблице', 'Цвет текста при отображении в таблице', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (216, 9, 'ref_table_name', 'Название базовой таблицы', 'Название базовой таблицы', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (292, 2, 'id_communication_object', 'Объект', 'Объект', 'tbl_io_communication_objects_references', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (297, 6, 'start_time', 'Актуален с', 'Актуален с', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (298, 6, 'finish_time', 'Актуален по', 'Актуален по', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (300, 2, 'id_param_category', 'Параметр в категории', 'Параметр в категории', 'tbl_cat_params', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (301, 9, 'value', 'Значение параметра', 'Значение параметра', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (302, 1, 'is_actual', 'Значение параметра актуально', 'Значение параметра актуально', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (303, 2, 'id_parameter', 'Параметр', 'Параметр', 'tbl_parameters', 'name', true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (304, 9, 'default_value', 'Значение по умолчанию', 'Значение по умолчанию', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (305, 1, 'is_read_only','Значение параметра не редактируемо', 'Значение параметра не редактируемо', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (312, 15, 'r_icon', 'Условный знак элемента', 'Условный знак элемента', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (313, 6, 'start_time', 'Начало потока', 'Начало потока', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (314, 6, 'finish_time', 'Окончание потока', 'Окончание потока', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (348, 31, 'uuid_t', 'Уникальный идентификатор (UUID)', 'UUID', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (359, 3, 'id_parent', 'Родитель', 'Родитель', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (392, 9, 'user_name', 'Имя пользователя', 'Имя пользователя', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (393, 8, 'id_user', 'ИД пользователя', 'ИД пользователя', null::varchar, null::varchar, true);
insert into tbl_parameters(id, id_param_type, code, name, title, table_name, column_name, is_system) values (404, 8, 'param_sort_order', 'Порядок следования параметра', 'Порядок следования параметра', null::varchar, null::varchar, true);
select setval('tbl_parameters_id_seq', 1000, true);
-- все пользовательские параметры начнутся с 1001
-- чтоб сохранить резерв для системных параметров
