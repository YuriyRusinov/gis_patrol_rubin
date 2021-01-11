insert into tbl_param_views (id, name) values (1, 'Чекбокс');
insert into tbl_param_views (id, name) values (2, 'выбор из списка (комбобокс)');
insert into tbl_param_views (id, name) values (3, 'дата');
insert into tbl_param_views (id, name) values (4, 'дата-время');
insert into tbl_param_views (id, name) values (5, 'строка текста');
insert into tbl_param_views (id, name) values (6, 'интервал');
insert into tbl_param_views (id, name) values (7, 'набор элементов');
insert into tbl_param_views (id, name) values (8, 'поле текста');
insert into tbl_param_views (id, name) values (9, 'строка текста фиксированной длины');
insert into tbl_param_views (id, name) values (10, 'Изображение JPG');
insert into tbl_param_views (id, name) values (11, 'Выбор цвета');
insert into tbl_param_views (id, name) values (12, 'Набор пространственных точек');
insert into tbl_param_views (id, name) values (13, 'Объект SVG');
insert into tbl_param_views (id, name) values (14, 'Видео-ролик');
insert into tbl_param_views (id, name) values (15, 'Время');
insert into tbl_param_views (id, name) values (16, 'ГИС-объект');
insert into tbl_param_views (id, name) values (17, 'ГИС-объект (geography)');
insert into tbl_param_views (id, name) values (18, 'Составной атрибут');
insert into tbl_param_views (id, name) values (19, 'Гистограмма');
insert into tbl_param_views (id, name) values (20, 'ГИС-объект (карта)');
insert into tbl_param_views (id, name) values (21, 'JSON Объект');
insert into tbl_param_views (id, name) values (22, 'JSON Binary Объект ');

select setval('tbl_param_views_id_seq', 22, true);

insert into tbl_parameter_types (id, id_param_view, name, code) values (1, 1, 'Логический', 'bool');
insert into tbl_parameter_types (id, id_param_view, name, code) values (2, 2, 'Элемент справочника', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (3, 2, 'Родитель/Потомок', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (4, 3, 'Дата', 'date');
insert into tbl_parameter_types (id, id_param_view, name, code) values (5, 4, 'Дата-время без указания временной зоны', 'timestamp');
insert into tbl_parameter_types (id, id_param_view, name, code) values (6, 4, 'Дата-время с указанием временной зоны', 'timestamptz');
insert into tbl_parameter_types (id, id_param_view, name, code) values (7, 5, 'Вещественная величина', 'float8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (8, 5, 'Целочисленная величина', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (9, 5, 'Строка', 'varchar');
insert into tbl_parameter_types (id, id_param_view, name, code) values (10, 6, 'Временной интервал (сутки)', 'int4[]');
insert into tbl_parameter_types (id, id_param_view, name, code) values (13, 8, 'Текст', 'text');
insert into tbl_parameter_types (id, id_param_view, name, code) values (14, 9, 'Строка фиксированной длины', 'varchar');
insert into tbl_parameter_types (id, id_param_view, name, code) values (15, 10, 'Изображение', 'varchar');
--insert into tbl_parameter_types (id, id_param_view, name, code) values (16, 5, 'Мандатная метка', 'maclabel');

insert into tbl_parameter_types (id, id_param_view, name, code) values (17, 7, 'Набор элементов справочника', 'int8[]');
insert into tbl_parameter_types (id, id_param_view, name, code) values (18, 11, 'Цвет записи в справочнике (фон)', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (19, 11, 'Ссылка на цвет записи (фон)', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (20, 8, 'xml-документ', 'xml');
insert into tbl_parameter_types (id, id_param_view, name, code) values (21, 6, 'Временной интервал (часы)', 'int4[3]');
insert into tbl_parameter_types (id, id_param_view, name, code) values (23, 13, 'Объект SVG', 'xml');
insert into tbl_parameter_types (id, id_param_view, name, code) values (24, 14, 'Видео-ролик', 'bytea');
insert into tbl_parameter_types (id, id_param_view, name, code) values (25, 11, 'Цвет записи в справочнике (текст)', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (26, 11, 'Ссылка на цвет записи (текст)', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (27, 15, 'Время', 'time');
insert into tbl_parameter_types (id, id_param_view, name, code) values (28, 16, 'ГИС-объект', 'geometry');
insert into tbl_parameter_types (id, id_param_view, name, code) values (29, 17, 'ГИС-объект (geography)', 'GEOGRAPHY');
insert into tbl_parameter_types (id, id_param_view, name, code) values (30, 5, 'Целочисленное значение (64 бита)', 'int8');
insert into tbl_parameter_types (id, id_param_view, name, code) values (31, 5, 'Уникальный идентификатор (UUID)', 'uuid');
insert into tbl_parameter_types (id, id_param_view, name, code) values (32, 18, 'Составной атрибут', 'varchar');
insert into tbl_parameter_types (id, id_param_view, name, code) values (33, 19, 'Гистограмма', 'varchar');
--insert into tbl_parameter_types (id, id_param_view, name, code) values (34, 20, 'ГИС-объект (векторный слой)', 'varchar');
--insert into tbl_parameter_types (id, id_param_view, name, code) values (35, 20, 'ГИС-объект (растровый слой)', 'varchar');
insert into tbl_parameter_types (id, id_param_view, name, code) values (36, 20, 'ГИС-объект (карта)', 'varchar');
insert into tbl_parameter_types (id, id_param_view, name, code) values (37, 21, 'Объект JSON', 'json');
insert into tbl_parameter_types (id, id_param_view, name, code) values (38, 22, 'Бинарный объект JSON', 'jsonb');
insert into tbl_parameter_types (id, id_param_view, name, code) values (39, 4, 'Дата-время (с миллисекундами)', 'timestamp');
insert into tbl_parameter_types (id, id_param_view, name, code) values (40, 14, 'Бинарные данные', 'bytea');

insert into tbl_parameter_types (id, id_param_view, name, code) values (41, 2, 'Ссылка на категорию (служебный атрибут)', 'int4');


select setval('tbl_parameter_types_id_seq', 41, true);
