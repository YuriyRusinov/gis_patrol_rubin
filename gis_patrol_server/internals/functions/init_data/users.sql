/*
Системные пользователи
*/
select safeCreateUser('yuriy', 'yuriy', true);
insert into users(id, role_name, id_maclabel, firstname, surname, lastname, family_name, information, email, db_user) values(1, 'yuriy', 1, 'Yury', 'Leonovich', 'Rusinov', 'Rusinov Yu.L.', 'Администратор системы', 'Y.L.Rusinov@rubin-spb.ru', 'yuriy');

select setval('patrol_roles_id_seq', 1, true);
