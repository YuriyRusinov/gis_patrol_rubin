insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (3, 10, null::integer, false, 'Типы категорий средств связи', 'SYSCATEGORY_3', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (4, 8, 3, true, 'Справочник типов категорий средств связи', 'SYSCATEGORY_4', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (5, 10, null::integer, false, 'Типы представлений параметров средств связи', 'SYSCATEGORY_5', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (6, 8, 5, true, 'Справочник типов представлений параметров средств связи', 'SYSCATEGORY_6', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (7, 10, null::integer, false, 'Типы параметров', 'SYSCATEGORY_7', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (8, 8, 7, true, 'Справочник типов параметров', 'SYSCATEGORY_8', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (9, 10, null::integer, false, 'Параметры', 'SYSCATEGORY_9', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (10, 8, 9, true, 'Справочник параметров', 'SYSCATEGORY_10', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (11, 10, null::integer, false, 'Категории', 'SYSCATEGORY_11', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (12, 8, 11, true, 'Справочник категорий', 'SYSCATEGORY_12', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (13, 10, null::integer, false, 'Средства коммуникаций', 'SYSCATEGORY_13', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (14, 8, 13, true, 'Справочник средств коммуникаций', 'SYSCATEGORY_14', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (17, 10, null::integer, false, 'Типы средств коммуникации', 'SYSCATEGORY_17', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (18, 8, 17, true, 'Справочник типов средств коммуникации', 'SYSCATEGORY_18', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (45, 10, null::integer, false, 'Грифы секретности', 'SYSCATEGORY_45', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (46, 8, 45, true, 'Справочник грифов секретности', 'SYSCATEGORY_46', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (49, 10, null::integer, false, 'Пользователи', 'SYSCATEGORY_49', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (50, 8, 49, true, 'Справочник пользователей', 'SYSCATEGORY_50', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (183, 10, null::integer, false, 'Значения параметров в информационных объектах', 'SYSCATEGORY_183', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (184, 8, 183, true, 'Справочник значений параметров в информационных объектах', 'SYSCATEGORY_184', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (185, 10, null::integer, false, 'Параметры в категориях', 'SYSCATEGORY_185', null::varchar, true);
insert into tbl_communication_categories (id, id_category_type, id_child, is_main, name, code, description, is_system) values (186, 8, 185, true, 'Справочник параметров в категориях', 'SYSCATEGORY_186', null::varchar, true);
select setval('tbl_communication_categories_id_seq', 500, true);
--
-- номера пользовательских категорий будут начинаться с 501,
-- предшествующие зарезервированы для возможных добавлений системных категорий
--
