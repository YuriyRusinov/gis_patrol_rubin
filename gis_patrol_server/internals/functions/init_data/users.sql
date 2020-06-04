/*
Системные пользователи
*/
select safeCreateUser('yuriy', 'yuriy', true);
insert into users(id, id_maclabel, firstname, surname, lastname, family_name, information, email, db_user) values(1, 1, 'Yury', 'Leonovich', 'Rusinov', 'Rusinov Yu.L.', 'Администратор системы', 'Y.L.Rusinov@rubin-spb.ru', 'yuriy');

select setval('users_id_seq', 1, true);
