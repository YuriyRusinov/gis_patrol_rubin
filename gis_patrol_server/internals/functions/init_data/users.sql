/*
Системные пользователи
*/
select safeCreateUser('yrusinov', 'yrusinov', true);
insert into users(id, id_maclabel, role_name, firstname, surname, lastname, family_name, information, email, db_user) values( 1, 1, 'yrusinov', 'Yury', 'Leonovich', 'Rusinov', 'Rusinov Yu.L.', 'Администратор системы', 'Y.L.Rusinov@rubin-spb.ru', 'yrusinov');

select setval('patrol_roles_id_seq', 1, true);
