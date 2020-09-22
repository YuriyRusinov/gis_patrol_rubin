--for linter
/*
insert into maclabels (id, name, mac_value) values (1, 'Несекретно', '{0,0}'::maclabel);
insert into maclabels (id, name, mac_value) values (2, 'Cекретно', '{1,0}'::maclabel);
insert into maclabels (id, name, mac_value) values ('Сов. секретно', '{2,0}'::maclabel);
*/


--for postgres
insert into maclabels (id, name, mac_value) values (1, 'Несекретно', (0,0));
insert into maclabels (id, name, mac_value) values (2, 'Cекретно', (1,0));
insert into maclabels (id, name, mac_value) values (3, 'Сов. секретно', (2,0));

