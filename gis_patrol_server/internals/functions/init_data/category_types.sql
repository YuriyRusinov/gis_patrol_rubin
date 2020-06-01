insert into tbl_category_type (id, name, description) values (1, 'Справочник', null);
insert into tbl_category_type (id, name, description) values (2, 'Журнал/Реестр', null);
insert into tbl_category_type (id, name, description) values (3, 'Документ', null);
insert into tbl_category_type (id, name, description) values (8, 'Системный справочник', 'Используется в качестве типа для категорий, которые являются системными. Например, справочник состояний; справочник атрибутов; справочник типов атрибутов; справочник типов информационных объектов.');
insert into tbl_category_type (id, name, description) values (9, 'Системный справочник категорий документов', 'Используется в качестве типа для системных информационных объектов, которые являются справочниками категорий информационных объектов');
insert into tbl_category_type (id, name, description) values (10, 'Подчиненная категория', 'Используется в качестве типа для категорий, которые являются подчиненными (описывают таблицы)');

select setval('tbl_category_type_id_seq', 10, true);
